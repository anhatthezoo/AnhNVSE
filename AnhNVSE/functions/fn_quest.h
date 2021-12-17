#pragma once

DEFINE_CMD_ALT_COND_PLUGIN(GetQuestCompletedAlt, GetQuestSucceeded, "", false, kParams_OneQuest)
DEFINE_COMMAND_PLUGIN(TestQuestFunc, "", 0 , 0, NULL);
 
typedef Set<TESForm*> TempFormList;
TempFormList* GetTempFormList();

__declspec(noinline) TempFormList* GetTempFormList()
{
	thread_local TempFormList s_tempFormList(0x40);
	return &s_tempFormList;
}

#if RUNTIME

bool Cmd_GetQuestCompletedAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	TESQuest* quest;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest) && quest)
	{
		*result = quest->IsQuestSuccessful();
	}
	return true;
};

bool Cmd_GetQuestCompletedAlt_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (auto const quest = (TESQuest*)arg1)
	{
		*result = quest->IsQuestSuccessful();
	}
	return true;
}

bool Cmd_TestQuestFunc_Execute(COMMAND_ARGS) {
	*result = 0;
	ListNode<BGSQuestObjective>* iter = (*g_thePlayer)->questObjectiveList.Head();
	BGSQuestObjective* objective;
	TESQuest* quest;
	TempFormList* tempList = GetTempFormList();
	tempList->Clear();
	do {
		objective = iter->data;

		quest = objective->quest;
		if (!tempList->Find(quest)) {
			tempList->Insert(quest);
		}
		
	} while (iter = iter->next);

	for (auto refIter = tempList->Begin(); refIter; ++refIter) {
		const char* tempString = refIter->GetFullName()->name.CStr();
		Console_Print(tempString);
	}

	return true;
}
#endif