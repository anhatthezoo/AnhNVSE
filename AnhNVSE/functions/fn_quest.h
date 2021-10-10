#pragma once

DEFINE_CMD_COND_PLUGIN(GetQuestCompletedAlt, "", 0, kParams_OneQuest)


#if RUNTIME
bool Cmd_GetQuestCompletedAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	TESQuest* quest;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest))
	{
		bool const bQuestFailed = (quest->flags & 0x40);
		bool const bQuestCompleted = (quest->flags * 0x2);

		*result = bQuestCompleted && !bQuestFailed;
	}
	return true;
};

bool Cmd_GetQuestCompletedAlt_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	TESQuest* quest = (TESQuest*)arg1;

	if (quest)
	{
		bool const bQuestFailed = (quest->flags & 0x40);
		bool const bQuestCompleted = (quest->flags * 0x2);

		*result = bQuestCompleted && !bQuestFailed;
	}
	return true;
}
#endif