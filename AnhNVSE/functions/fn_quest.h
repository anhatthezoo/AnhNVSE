#pragma once

DEFINE_CMD_ALT_COND_PLUGIN(GetQuestCompletedAlt, GetQuestSucceeded, "", false, kParams_OneQuest)


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
#endif