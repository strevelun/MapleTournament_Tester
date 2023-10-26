#pragma once

enum class ePacketType
{
	None,
	S_EnterLobby,
	C_Exit,
	C_OKLogin,
	S_OKLogin,
	S_FailedLogin,
	C_CreateRoom,
	S_CreateRoom,
	C_Chat,
	S_Chat,
	C_JoinRoom,
	S_JoinRoom,
	S_JoinRoomFail,
	C_LeaveRoom,
	S_UpdateRoomMemberLeave,
	S_NotifyJoinedUser,
	C_CheckRoomReady,
	S_CheckRoomReadyOK,
	S_CheckRoomReadyFail,
	C_UserRoomReady,
	S_UpdateUserState,
	S_UpdateWaitingRoomBtn,
	S_UpdateUserType,
	C_InGameReady,
	S_InGameReady,
	C_UpdateUserListPage,
	S_UpdateUserListPage,
	C_UpdateRoomListPage,
	S_UpdateRoomListPage,
};

enum class eSkillType
{
	None,
	AttackCloud,
	LeftMove,
	LeftDoubleMove,

	NumOfSkills,
};

enum class eMemberType
{
	None,
	Member,
	Owner
};

enum class eMemberState
{
	None,
	Wait,
	Ready
};

enum class eType
{
	Tile,
	Block,
	Character,
	None
};

enum class eSessionState
{
	None,
	Login,
	Lobby,
	WatingRoom,
	InGame
};