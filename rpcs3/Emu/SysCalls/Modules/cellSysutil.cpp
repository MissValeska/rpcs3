#include "stdafx.h"
#include "Emu/SysCalls/SysCalls.h"
#include "Emu/SysCalls/SC_FUNC.h"
#include "Emu/Audio/sysutil_audio.h"

// Parameter IDs
enum
{
	//Integers
	CELL_SYSUTIL_SYSTEMPARAM_ID_LANG							= 0x0111,
	CELL_SYSUTIL_SYSTEMPARAM_ID_ENTER_BUTTON_ASSIGN				= 0x0112,
	CELL_SYSUTIL_SYSTEMPARAM_ID_DATE_FORMAT						= 0x0114,
	CELL_SYSUTIL_SYSTEMPARAM_ID_TIME_FORMAT						= 0x0115,
	CELL_SYSUTIL_SYSTEMPARAM_ID_TIMEZONE						= 0x0116,
	CELL_SYSUTIL_SYSTEMPARAM_ID_SUMMERTIME						= 0x0117,
	CELL_SYSUTIL_SYSTEMPARAM_ID_GAME_PARENTAL_LEVEL				= 0x0121,
	CELL_SYSUTIL_SYSTEMPARAM_ID_GAME_PARENTAL_LEVEL0_RESTRICT	= 0x0123,
	CELL_SYSUTIL_SYSTEMPARAM_ID_CURRENT_USER_HAS_NP_ACCOUNT		= 0x0141,
	CELL_SYSUTIL_SYSTEMPARAM_ID_CAMERA_PLFREQ					= 0x0151,
	CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_RUMBLE						= 0x0152,
	CELL_SYSUTIL_SYSTEMPARAM_ID_KEYBOARD_TYPE					= 0x0153,
	CELL_SYSUTIL_SYSTEMPARAM_ID_JAPANESE_KEYBOARD_ENTRY_METHOD	= 0x0154,
	CELL_SYSUTIL_SYSTEMPARAM_ID_CHINESE_KEYBOARD_ENTRY_METHOD	= 0x0155,
	CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_AUTOOFF						= 0x0156,

	//Strings
	CELL_SYSUTIL_SYSTEMPARAM_ID_NICKNAME						= 0x113,
	CELL_SYSUTIL_SYSTEMPARAM_ID_CURRENT_USERNAME				= 0x131,
};

enum
{
	CELL_SYSUTIL_LANG_JAPANESE		= 0,
	CELL_SYSUTIL_LANG_ENGLISH_US	= 1,
	CELL_SYSUTIL_LANG_FRENCH		= 2,
	CELL_SYSUTIL_LANG_SPANISH		= 3,
	CELL_SYSUTIL_LANG_GERMAN		= 4,
	CELL_SYSUTIL_LANG_ITALIAN		= 5,
	CELL_SYSUTIL_LANG_DUTCH			= 6,
	CELL_SYSUTIL_LANG_PORTUGUESE_PT	= 7,
	CELL_SYSUTIL_LANG_RUSSIAN		= 8,
	CELL_SYSUTIL_LANG_KOREAN		= 9,
	CELL_SYSUTIL_LANG_CHINESE_T		= 10,
	CELL_SYSUTIL_LANG_CHINESE_S		= 11,
	CELL_SYSUTIL_LANG_FINNISH		= 12,
	CELL_SYSUTIL_LANG_SWEDISH		= 13,
	CELL_SYSUTIL_LANG_DANISH		= 14,
	CELL_SYSUTIL_LANG_NORWEGIAN		= 15,
	CELL_SYSUTIL_LANG_POLISH		= 16,
	CELL_SYSUTIL_LANG_PORTUGUESE_BR	= 17,
	CELL_SYSUTIL_LANG_ENGLISH_GB	= 18,
};

enum
{
	CELL_SYSUTIL_ENTER_BUTTON_ASSIGN_CIRCLE = 0,
	CELL_SYSUTIL_ENTER_BUTTON_ASSIGN_CROSS	= 1,
};

enum
{
	CELL_SYSUTIL_DATE_FMT_YYYYMMDD = 0,
	CELL_SYSUTIL_DATE_FMT_DDMMYYYY = 1,
	CELL_SYSUTIL_DATE_FMT_MMDDYYYY = 2,
};

enum
{
	CELL_SYSUTIL_TIME_FMT_CLOCK12 = 0,
	CELL_SYSUTIL_TIME_FMT_CLOCK24 = 1,
};

enum
{
	CELL_SYSUTIL_GAME_PARENTAL_OFF		= 0,
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL01	= 1,
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL02	= 2,
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL03	= 3,
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL04	= 4,
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL05	= 5,
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL06	= 6,
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL07	= 7,
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL08	= 8,
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL09	= 9,
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL10	= 10,
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL11	= 11,
};

enum
{
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL0_RESTRICT_OFF	= 0,
	CELL_SYSUTIL_GAME_PARENTAL_LEVEL0_RESTRICT_ON	= 1,
};

enum
{
	CELL_SYSUTIL_CAMERA_PLFREQ_DISABLED			= 0,
	CELL_SYSUTIL_CAMERA_PLFREQ_50HZ				= 1,
	CELL_SYSUTIL_CAMERA_PLFREQ_60HZ				= 2,
	CELL_SYSUTIL_CAMERA_PLFREQ_DEVCIE_DEPEND	= 4,
};

enum
{
	CELL_SYSUTIL_PAD_RUMBLE_OFF	= 0,
	CELL_SYSUTIL_PAD_RUMBLE_ON	= 1,
};


enum
{
	CELL_MSGDIALOG_BUTTON_NONE		= -1,
	CELL_MSGDIALOG_BUTTON_INVALID	= 0,
	CELL_MSGDIALOG_BUTTON_OK		= 1,
	CELL_MSGDIALOG_BUTTON_YES		= 1,
	CELL_MSGDIALOG_BUTTON_NO		= 2,
	CELL_MSGDIALOG_BUTTON_ESCAPE	= 3,
};

enum{
	CELL_SYSCACHE_RET_OK_CLEARED		= 0,
	CELL_SYSCACHE_RET_OK_RELAYED		= 1,

	CELL_SYSCACHE_ID_SIZE				= 32,
	CELL_SYSCACHE_PATH_MAX				= 1055,

	CELL_SYSCACHE_ERROR_ACCESS_ERROR	= 0x8002bc01,//I don't think we need this
	CELL_SYSCACHE_ERROR_INTERNAL		= 0x8002bc02,//not really useful, if we run out of HD space sysfs should handle that

	CELL_SYSCACHE_ERROR_PARAM			= 0x8002bc03,
	CELL_SYSCACHE_ERROR_NOTMOUNTED		= 0x8002bc04,//we don't really need to simulate the mounting, so this is probably useless
};

enum CellMsgDialogType
{
	CELL_MSGDIALOG_DIALOG_TYPE_ERROR	= 0x00000000,
	CELL_MSGDIALOG_DIALOG_TYPE_NORMAL	= 0x00000001,

	CELL_MSGDIALOG_BUTTON_TYPE_NONE		= 0x00000000,
	CELL_MSGDIALOG_BUTTON_TYPE_YESNO	= 0x00000010,

	CELL_MSGDIALOG_DEFAULT_CURSOR_YES	= 0x00000000,
	CELL_MSGDIALOG_DEFAULT_CURSOR_NO	= 0x00000100,
};

typedef void (*CellMsgDialogCallback)(int buttonType, mem_ptr_t<void> userData);

void cellSysutil_init();
Module cellSysutil(0x0015, cellSysutil_init);

int cellSysutilGetSystemParamInt(int id, mem32_t value)
{
	cellSysutil.Log("cellSysutilGetSystemParamInt(id=0x%x, value_addr=0x%x)", id, value.GetAddr());

	if(!value.IsGood())
	{
		return CELL_EFAULT;
	}

	switch(id)
	{
	case CELL_SYSUTIL_SYSTEMPARAM_ID_LANG:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_LANG");
		value = CELL_SYSUTIL_LANG_ENGLISH_US;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_ENTER_BUTTON_ASSIGN:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_ENTER_BUTTON_ASSIGN");
		value = CELL_SYSUTIL_ENTER_BUTTON_ASSIGN_CROSS;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_DATE_FORMAT:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_DATE_FORMAT");
		value = CELL_SYSUTIL_DATE_FMT_DDMMYYYY;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_TIME_FORMAT:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_TIME_FORMAT");
		value = CELL_SYSUTIL_TIME_FMT_CLOCK24;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_TIMEZONE:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_TIMEZONE");
		value = 3;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_SUMMERTIME:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_SUMMERTIME");
		value = 1;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_GAME_PARENTAL_LEVEL:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_GAME_PARENTAL_LEVEL");
		value = CELL_SYSUTIL_GAME_PARENTAL_OFF;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_GAME_PARENTAL_LEVEL0_RESTRICT:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_GAME_PARENTAL_LEVEL0_RESTRICT");
		value = CELL_SYSUTIL_GAME_PARENTAL_LEVEL0_RESTRICT_OFF;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_CURRENT_USER_HAS_NP_ACCOUNT:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_CURRENT_USER_HAS_NP_ACCOUNT");
		value = 0;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_CAMERA_PLFREQ:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_CAMERA_PLFREQ");
		value = CELL_SYSUTIL_CAMERA_PLFREQ_DISABLED;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_RUMBLE:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_RUMBLE");
		value = CELL_SYSUTIL_PAD_RUMBLE_OFF;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_KEYBOARD_TYPE:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_KEYBOARD_TYPE");
		value = 0;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_JAPANESE_KEYBOARD_ENTRY_METHOD:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_JAPANESE_KEYBOARD_ENTRY_METHOD");
		value = 0;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_CHINESE_KEYBOARD_ENTRY_METHOD:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_CHINESE_KEYBOARD_ENTRY_METHOD");
		value = 0;
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_AUTOOFF:
		cellSysutil.Warning("cellSysutilGetSystemParamInt: CELL_SYSUTIL_SYSTEMPARAM_ID_PAD_AUTOOFF");
		value = 0;
	break;

	default:
		return CELL_EINVAL;
	}

	return CELL_OK;
}

int cellSysutilGetSystemParamString(s32 id, mem_list_ptr_t<u8> buf, u32 bufsize)
{
	cellSysutil.Log("cellSysutilGetSystemParamString(id=%d, buf_addr=0x%x, bufsize=%d)", id, buf.GetAddr(), bufsize);

	if (!buf.IsGood())
		return CELL_EFAULT;

	memset(buf, 0, bufsize);

	switch(id)
	{
	case CELL_SYSUTIL_SYSTEMPARAM_ID_NICKNAME:
		cellSysutil.Warning("cellSysutilGetSystemParamString: CELL_SYSUTIL_SYSTEMPARAM_ID_NICKNAME");
		memcpy(buf, "Unknown", 8); //for example
	break;

	case CELL_SYSUTIL_SYSTEMPARAM_ID_CURRENT_USERNAME:
		cellSysutil.Warning("cellSysutilGetSystemParamString: CELL_SYSUTIL_SYSTEMPARAM_ID_CURRENT_USERNAME");
		memcpy(buf, "Unknown", 8);
	break;

	default:
		return CELL_EINVAL;
	}

	return CELL_OK;
}

int cellVideoOutGetState(u32 videoOut, u32 deviceIndex, u32 state_addr)
{
	cellSysutil.Log("cellVideoOutGetState(videoOut=0x%x, deviceIndex=0x%x, state_addr=0x%x)", videoOut, deviceIndex, state_addr);

	if(deviceIndex) return CELL_VIDEO_OUT_ERROR_DEVICE_NOT_FOUND;

	CellVideoOutState state;
	memset(&state, 0, sizeof(CellVideoOutState));

	switch(videoOut)
	{
		case CELL_VIDEO_OUT_PRIMARY:
		{
			state.colorSpace = Emu.GetGSManager().GetColorSpace();
			state.state = Emu.GetGSManager().GetState();
			state.displayMode.resolutionId = Emu.GetGSManager().GetInfo().mode.resolutionId;
			state.displayMode.scanMode = Emu.GetGSManager().GetInfo().mode.scanMode;
			state.displayMode.conversion = Emu.GetGSManager().GetInfo().mode.conversion;
			state.displayMode.aspect = Emu.GetGSManager().GetInfo().mode.aspect;
			state.displayMode.refreshRates = re(Emu.GetGSManager().GetInfo().mode.refreshRates);

			Memory.WriteData(state_addr, state);
		}
		return CELL_VIDEO_OUT_SUCCEEDED;

		case CELL_VIDEO_OUT_SECONDARY:
		{
			state.colorSpace = CELL_VIDEO_OUT_COLOR_SPACE_RGB;
			state.state = CELL_VIDEO_OUT_OUTPUT_STATE_ENABLED;

			Memory.WriteData(state_addr, state);
		}
		return CELL_VIDEO_OUT_SUCCEEDED;
	}

	return CELL_VIDEO_OUT_ERROR_UNSUPPORTED_VIDEO_OUT;
}

int cellVideoOutGetResolution(u32 resolutionId, u32 resolution_addr)
{
	cellSysutil.Log("cellVideoOutGetResolution(resolutionId=%d, resolution_addr=0x%x)",
		resolutionId, resolution_addr);

	if(!Memory.IsGoodAddr(resolution_addr, sizeof(CellVideoOutResolution)))
	{
		return CELL_EFAULT;
	}

	u32 num = ResolutionIdToNum(resolutionId);

	if(!num)
	{
		return CELL_EINVAL;
	}

	CellVideoOutResolution res;
	re(res.width, ResolutionTable[num].width);
	re(res.height, ResolutionTable[num].height);

	Memory.WriteData(resolution_addr, res);

	return CELL_VIDEO_OUT_SUCCEEDED;
}

int cellVideoOutConfigure(u32 videoOut, u32 config_addr, u32 option_addr, u32 waitForEvent)
{
	cellSysutil.Warning("cellVideoOutConfigure(videoOut=%d, config_addr=0x%x, option_addr=0x%x, waitForEvent=0x%x)",
		videoOut, config_addr, option_addr, waitForEvent);

	if(!Memory.IsGoodAddr(config_addr, sizeof(CellVideoOutConfiguration)))
	{
		return CELL_EFAULT;
	}

	CellVideoOutConfiguration& config = (CellVideoOutConfiguration&)Memory[config_addr];

	switch(videoOut)
	{
	case CELL_VIDEO_OUT_PRIMARY:
		if(config.resolutionId)
		{
			Emu.GetGSManager().GetInfo().mode.resolutionId = config.resolutionId;
		}

		Emu.GetGSManager().GetInfo().mode.format = config.format;

		if(config.aspect)
		{
			Emu.GetGSManager().GetInfo().mode.aspect = config.aspect;
		}

		if(config.pitch)
		{
			Emu.GetGSManager().GetInfo().mode.pitch = re(config.pitch);
		}

		return CELL_VIDEO_OUT_SUCCEEDED;

	case CELL_VIDEO_OUT_SECONDARY:
		return CELL_VIDEO_OUT_SUCCEEDED;
	}

	return CELL_VIDEO_OUT_ERROR_UNSUPPORTED_VIDEO_OUT;
}

int cellVideoOutGetConfiguration(u32 videoOut, u32 config_addr, u32 option_addr)
{
	cellSysutil.Warning("cellVideoOutGetConfiguration(videoOut=%d, config_addr=0x%x, option_addr=0x%x)",
		videoOut, config_addr, option_addr);

	if(!Memory.IsGoodAddr(config_addr, sizeof(CellVideoOutConfiguration))) return CELL_EFAULT;

	CellVideoOutConfiguration config;
	memset(&config, 0, sizeof(CellVideoOutConfiguration));

	switch(videoOut)
	{
	case CELL_VIDEO_OUT_PRIMARY:
		config.resolutionId = Emu.GetGSManager().GetInfo().mode.resolutionId;
		config.format = Emu.GetGSManager().GetInfo().mode.format;
		config.aspect = Emu.GetGSManager().GetInfo().mode.aspect;
		config.pitch = re(Emu.GetGSManager().GetInfo().mode.pitch);

		Memory.WriteData(config_addr, config);

		return CELL_VIDEO_OUT_SUCCEEDED;

	case CELL_VIDEO_OUT_SECONDARY:
		Memory.WriteData(config_addr, config);

		return CELL_VIDEO_OUT_SUCCEEDED;
	}

	return CELL_VIDEO_OUT_ERROR_UNSUPPORTED_VIDEO_OUT;
}

int cellVideoOutGetDeviceInfo(u32 videoOut, u32 deviceIndex, mem_ptr_t<CellVideoOutDeviceInfo> info)
{
	cellSysutil.Warning("cellVideoOutGetDeviceInfo(videoOut=%u, deviceIndex=%u, info_addr=0x%x)",
		videoOut, deviceIndex, info.GetAddr());

	if(deviceIndex) return CELL_VIDEO_OUT_ERROR_DEVICE_NOT_FOUND;

	// Use standard dummy values for now.
	info->portType = CELL_VIDEO_OUT_PORT_HDMI;
	info->colorSpace = Emu.GetGSManager().GetColorSpace();
	info->latency = 1000;
	info->availableModeCount = 1;
	info->state = CELL_VIDEO_OUT_DEVICE_STATE_AVAILABLE;
	info->rgbOutputRange = 1;
	info->colorInfo.blueX = 0xFFFF;
	info->colorInfo.blueY = 0xFFFF;
	info->colorInfo.greenX = 0xFFFF;
	info->colorInfo.greenY = 0xFFFF;
	info->colorInfo.redX = 0xFFFF;
	info->colorInfo.redY = 0xFFFF;
	info->colorInfo.whiteX = 0xFFFF;
	info->colorInfo.whiteY = 0xFFFF;
	info->colorInfo.gamma = 100;
	info->availableModes[0].aspect = 0;
	info->availableModes[0].conversion = 0;
	info->availableModes[0].refreshRates = 0xF;
	info->availableModes[0].resolutionId = 1;
	info->availableModes[0].scanMode = 0;

	return CELL_OK;
}

int cellVideoOutGetNumberOfDevice(u32 videoOut)
{
	cellSysutil.Warning("cellVideoOutGetNumberOfDevice(videoOut=%d)", videoOut);

	switch(videoOut)
	{
	case CELL_VIDEO_OUT_PRIMARY: return 1;
	case CELL_VIDEO_OUT_SECONDARY: return 0;
	}

	return CELL_VIDEO_OUT_ERROR_UNSUPPORTED_VIDEO_OUT;
}

int cellVideoOutGetResolutionAvailability(u32 videoOut, u32 resolutionId, u32 aspect, u32 option)
{
	cellSysutil.Warning("cellVideoOutGetResolutionAvailability(videoOut=%d, resolutionId=0x%x, option_addr=0x%x, aspect=0x%x, option=0x%x)",
		videoOut, resolutionId, aspect, option);

	if(!ResolutionIdToNum(resolutionId))
	{
		return CELL_EINVAL;
	}

	switch(videoOut)
	{
	case CELL_VIDEO_OUT_PRIMARY: return 1;
	case CELL_VIDEO_OUT_SECONDARY: return 0;
	}

	return CELL_VIDEO_OUT_ERROR_UNSUPPORTED_VIDEO_OUT;
}

extern std::atomic<u32> g_FsAioReadID;
extern std::atomic<u32> g_FsAioReadCur;

int cellSysutilCheckCallback()
{
	cellSysutil.Log("cellSysutilCheckCallback()");

	Emu.GetCallbackManager().m_exit_callback.Check();

	CPUThread& thr = Emu.GetCallbackThread();

	while (thr.IsAlive() || (g_FsAioReadCur < g_FsAioReadID))
	{
		Sleep(1);
		if (Emu.IsStopped())
		{
			ConLog.Warning("cellSysutilCheckCallback() aborted");
			break;
		}
	}

	return CELL_OK;
}

int cellSysutilRegisterCallback(int slot, u64 func_addr, u64 userdata)
{
	cellSysutil.Warning("cellSysutilRegisterCallback(slot=%d, func_addr=0x%llx, userdata=0x%llx)", slot, func_addr, userdata);

	Emu.GetCallbackManager().m_exit_callback.Register(slot, func_addr, userdata);

	wxGetApp().SendDbgCommand(DID_REGISTRED_CALLBACK);

	return CELL_OK;
}

int cellSysutilUnregisterCallback(int slot)
{
	cellSysutil.Warning("cellSysutilUnregisterCallback(slot=%d)", slot);

	Emu.GetCallbackManager().m_exit_callback.Unregister(slot);

	wxGetApp().SendDbgCommand(DID_UNREGISTRED_CALLBACK);

	return CELL_OK;
}

int cellMsgDialogOpen2(u32 type, char* msgString, mem_func_ptr_t<CellMsgDialogCallback> callback, mem_ptr_t<void> userData, u32 extParam)
{
	long style = 0;

	if(type & CELL_MSGDIALOG_DIALOG_TYPE_NORMAL)
	{
		style |= wxICON_EXCLAMATION;
	}
	else
	{
		style |= wxICON_ERROR;
	}

	if(type & CELL_MSGDIALOG_BUTTON_TYPE_YESNO)
	{
		style |= wxYES_NO;
	}
	else
	{
		style |= wxOK;
	}

	int res = wxMessageBox(wxString(msgString, wxConvUTF8), wxGetApp().GetAppName(), style);

	u64 status;

	switch(res)
	{
	case wxOK: status = CELL_MSGDIALOG_BUTTON_OK; break;
	case wxYES: status = CELL_MSGDIALOG_BUTTON_YES; break;
	case wxNO: status = CELL_MSGDIALOG_BUTTON_NO; break;

	default:
		if(res)
		{
			status = CELL_MSGDIALOG_BUTTON_INVALID;
			break;
		}

		status = CELL_MSGDIALOG_BUTTON_NONE;
	break;
	}

	if(callback)
		callback(status, userData);

	return CELL_OK;
}

int cellMsgDialogOpenErrorCode(u32 errorCode, mem_func_ptr_t<CellMsgDialogCallback> callback, mem_ptr_t<void> userData, u32 extParam)
{
	cellSysutil.Warning("cellMsgDialogOpenErrorCode(errorCode=0x%x, callback_addr=0x%x, userData=%d, extParam=%d)",
		errorCode, callback.GetAddr(), userData, extParam);

	std::string errorMessage;
	switch(errorCode)
	{
	// Generic errors
	case 0x80010001: errorMessage = "The resource is temporarily unavailable."; break;
	case 0x80010002: errorMessage = "Invalid argument or flag."; break;
	case 0x80010003: errorMessage = "The feature is not yet implemented."; break;
	case 0x80010004: errorMessage = "Memory allocation failed."; break;
	case 0x80010005: errorMessage = "The resource with the specified identifier does not exist."; break;
	case 0x80010006: errorMessage = "The file does not exist."; break;
	case 0x80010007: errorMessage = "The file is in unrecognized format / The file is not a valid ELF file."; break;
	case 0x80010008: errorMessage = "Resource deadlock is avoided."; break;
	case 0x80010009: errorMessage = "Operation not permitted."; break;
	case 0x8001000A: errorMessage = "The device or resource is bus."; break;
	case 0x8001000B: errorMessage = "The operation is timed ou."; break;
	case 0x8001000C: errorMessage = "The operation is aborte."; break;
	case 0x8001000D: errorMessage = "Invalid memory access."; break;
	case 0x8001000F: errorMessage = "State of the target thread is invalid."; break;
	case 0x80010010: errorMessage = "Alignment is invalid."; break;
	case 0x80010011: errorMessage = "Shortage of the kernel resources."; break;
	case 0x80010012: errorMessage = "The file is a directory."; break;
	case 0x80010013: errorMessage = "Operation canceled."; break;
	case 0x80010014: errorMessage = "Entry already exists."; break;
	case 0x80010015: errorMessage = "Port is already connected."; break;
	case 0x80010016: errorMessage = "Port is not connected."; break;
	case 0x80010017: errorMessage = "Failure in authorizing SELF. Program authentication fail."; break;
	case 0x80010018: errorMessage = "The file is not MSELF."; break;
	case 0x80010019: errorMessage = "System version error."; break;
	case 0x8001001A: errorMessage = "Fatal system error occurred while authorizing SELF. SELF auth failure."; break;
	case 0x8001001B: errorMessage = "Math domain violation."; break;
	case 0x8001001C: errorMessage = "Math range violation."; break;
	case 0x8001001D: errorMessage = "Illegal multi-byte sequence in input."; break;
	case 0x8001001E: errorMessage = "File position error."; break;
	case 0x8001001F: errorMessage = "Syscall was interrupted."; break;
	case 0x80010020: errorMessage = "File too large."; break;
	case 0x80010021: errorMessage = "Too many links."; break;
	case 0x80010022: errorMessage = "File table overflow."; break;
	case 0x80010023: errorMessage = "No space left on device."; break;
	case 0x80010024: errorMessage = "Not a TTY."; break;
	case 0x80010025: errorMessage = "Broken pipe."; break;
	case 0x80010026: errorMessage = "Read-only filesystem."; break;
	case 0x80010027: errorMessage = "Illegal seek."; break;
	case 0x80010028: errorMessage = "Arg list too long."; break;
	case 0x80010029: errorMessage = "Access violation."; break;
	case 0x8001002A: errorMessage = "Invalid file descriptor."; break;
	case 0x8001002B: errorMessage = "Filesystem mounting failed."; break;
	case 0x8001002C: errorMessage = "Too many files open."; break;
	case 0x8001002D: errorMessage = "No device."; break;
	case 0x8001002E: errorMessage = "Not a directory."; break;
	case 0x8001002F: errorMessage = "No such device or IO."; break;
	case 0x80010030: errorMessage = "Cross-device link error."; break;
	case 0x80010031: errorMessage = "Bad Message."; break;
	case 0x80010032: errorMessage = "In progress."; break;
	case 0x80010033: errorMessage = "Message size error."; break;
	case 0x80010034: errorMessage = "Name too long."; break;
	case 0x80010035: errorMessage = "No lock."; break;
	case 0x80010036: errorMessage = "Not empty."; break;
	case 0x80010037: errorMessage = "Not supported."; break;
	case 0x80010038: errorMessage = "File-system specific error."; break;
	case 0x80010039: errorMessage = "Overflow occured."; break;
	case 0x8001003A: errorMessage = "Filesystem not mounted."; break;
	case 0x8001003B: errorMessage = "Not SData."; break;
	case 0x8001003C: errorMessage = "Incorrect version in sys_load_param."; break;
	case 0x8001003D: errorMessage = "Pointer is null."; break;
	case 0x8001003E: errorMessage = "Pointer is null."; break;
	default: errorMessage = "An error has occurred."; break;
	}

	char errorCodeHex [9];
	sprintf(errorCodeHex, "%08x", errorCode);
	errorMessage.append("\n(");
	errorMessage.append(errorCodeHex);
	errorMessage.append(")\n");

	u64 status;
	int res = wxMessageBox(errorMessage, wxGetApp().GetAppName(), wxICON_ERROR | wxOK);
	switch(res)
	{
	case wxOK: status = CELL_MSGDIALOG_BUTTON_OK; break;
	default:
		if(res)
		{
			status = CELL_MSGDIALOG_BUTTON_INVALID;
			break;
		}

		status = CELL_MSGDIALOG_BUTTON_NONE;
	break;
	}

	if(callback)
		callback(status, userData);

	return CELL_OK;
}


int cellAudioOutGetSoundAvailability(u32 audioOut, u32 type, u32 fs, u32 option)
{
	cellSysutil.Warning("cellAudioOutGetSoundAvailability(audioOut=%d, type=%d, fs=0x%x, option=%d)",
		audioOut, type, fs, option);

	option = 0;

	int available = 2; // should be at least 2

	switch(fs)
	{
		case CELL_AUDIO_OUT_FS_32KHZ:
		case CELL_AUDIO_OUT_FS_44KHZ:
		case CELL_AUDIO_OUT_FS_48KHZ:
		case CELL_AUDIO_OUT_FS_88KHZ:
		case CELL_AUDIO_OUT_FS_96KHZ:
		case CELL_AUDIO_OUT_FS_176KHZ:
		case CELL_AUDIO_OUT_FS_192KHZ:
			break;

		default: return CELL_AUDIO_OUT_ERROR_UNSUPPORTED_SOUND_MODE;
	}

	switch(type)
	{
		case CELL_AUDIO_OUT_CODING_TYPE_LPCM: break;
		case CELL_AUDIO_OUT_CODING_TYPE_AC3: available = 0; break;
		case CELL_AUDIO_OUT_CODING_TYPE_DTS: available = 0; break;

		default: return CELL_AUDIO_OUT_ERROR_UNSUPPORTED_SOUND_MODE;
	}

	switch(audioOut)
	{
		case CELL_AUDIO_OUT_PRIMARY: return available;
		case CELL_AUDIO_OUT_SECONDARY: return 0;
	}

	return CELL_AUDIO_OUT_ERROR_ILLEGAL_CONFIGURATION;
}

int cellAudioOutGetSoundAvailability2(u32 audioOut, u32 type, u32 fs, u32 ch, u32 option)
{
	cellSysutil.Warning("cellAudioOutGetSoundAvailability2(audioOut=%d, type=%d, fs=0x%x, ch=%d, option=%d)",
		audioOut, type, fs, ch, option);

	option = 0;

	int available = 2; // should be at least 2

	switch(fs)
	{
		case CELL_AUDIO_OUT_FS_32KHZ:
		case CELL_AUDIO_OUT_FS_44KHZ:
		case CELL_AUDIO_OUT_FS_48KHZ:
		case CELL_AUDIO_OUT_FS_88KHZ:
		case CELL_AUDIO_OUT_FS_96KHZ:
		case CELL_AUDIO_OUT_FS_176KHZ:
		case CELL_AUDIO_OUT_FS_192KHZ:
			break;

		default: return CELL_AUDIO_OUT_ERROR_UNSUPPORTED_SOUND_MODE;
	}

	switch(ch)
	{
		case 2: break;
		case 6: available = 0; break;
		case 8: available = 0; break;

		default: return CELL_AUDIO_OUT_ERROR_UNSUPPORTED_SOUND_MODE;
	}

	switch(type)
	{
		case CELL_AUDIO_OUT_CODING_TYPE_LPCM: break;
		case CELL_AUDIO_OUT_CODING_TYPE_AC3: available = 0; break;
		case CELL_AUDIO_OUT_CODING_TYPE_DTS: available = 0; break;

		default: return CELL_AUDIO_OUT_ERROR_UNSUPPORTED_SOUND_MODE;
	}

	switch(audioOut)
	{
		case CELL_AUDIO_OUT_PRIMARY: return available;
		case CELL_AUDIO_OUT_SECONDARY: return 0;
	}

	return CELL_AUDIO_OUT_ERROR_ILLEGAL_CONFIGURATION;
}

int cellAudioOutGetState(u32 audioOut, u32 deviceIndex, u32 state_addr)
{
	cellSysutil.Warning("cellAudioOutGetState(audioOut=0x%x,deviceIndex=0x%x,state_addr=0x%x)",audioOut,deviceIndex,state_addr);
	CellAudioOutState state;
	memset(&state, 0, sizeof(CellAudioOutState));

	switch(audioOut)
	{
		case CELL_AUDIO_OUT_PRIMARY:
		{
			state.state = Emu.GetAudioManager().GetState();
			state.soundMode.type = Emu.GetAudioManager().GetInfo().mode.type;
			state.soundMode.channel = Emu.GetAudioManager().GetInfo().mode.channel;
			state.soundMode.fs = Emu.GetAudioManager().GetInfo().mode.fs;
			state.soundMode.layout = Emu.GetAudioManager().GetInfo().mode.layout;

			Memory.WriteData(state_addr, state);
		}
		return CELL_AUDIO_OUT_SUCCEEDED;

		case CELL_AUDIO_OUT_SECONDARY:
		{
			state.state = CELL_AUDIO_OUT_OUTPUT_STATE_ENABLED;

			Memory.WriteData(state_addr, state);
		}
		return CELL_AUDIO_OUT_SUCCEEDED;
	}

	return CELL_AUDIO_OUT_ERROR_UNSUPPORTED_AUDIO_OUT;
}

int cellAudioOutConfigure(u32 audioOut, mem_ptr_t<CellAudioOutConfiguration> config, mem_ptr_t<CellAudioOutOption> option, u32 waitForEvent)
{
	cellSysutil.Warning("cellAudioOutConfigure(audioOut=%d, config_addr=0x%x, option_addr=0x%x, (!)waitForEvent=%d)",
		audioOut, config.GetAddr(), option.GetAddr(), waitForEvent);

	if (!config.IsGood())
	{
		return CELL_EFAULT;
	}

	switch(audioOut)
	{
	case CELL_AUDIO_OUT_PRIMARY:
		if (config->channel)
		{
			Emu.GetAudioManager().GetInfo().mode.channel = config->channel;
		}

		Emu.GetAudioManager().GetInfo().mode.encoder = config->encoder;

		if(config->downMixer)
		{
			Emu.GetAudioManager().GetInfo().mode.downMixer = config->downMixer;
		}

		return CELL_AUDIO_OUT_SUCCEEDED;

	case CELL_AUDIO_OUT_SECONDARY:
		return CELL_AUDIO_OUT_SUCCEEDED;
	}

	return CELL_AUDIO_OUT_ERROR_UNSUPPORTED_AUDIO_OUT;
}

int cellAudioOutGetConfiguration(u32 audioOut, u32 config_addr, u32 option_addr)
{
	cellSysutil.Warning("cellAudioOutGetConfiguration(audioOut=%d, config_addr=0x%x, option_addr=0x%x)",
		audioOut, config_addr, option_addr);

	if(!Memory.IsGoodAddr(config_addr, sizeof(CellAudioOutConfiguration))) return CELL_EFAULT;

	CellAudioOutConfiguration config;
	memset(&config, 0, sizeof(CellAudioOutConfiguration));

	switch(audioOut)
	{
		case CELL_AUDIO_OUT_PRIMARY:
		config.channel = Emu.GetAudioManager().GetInfo().mode.channel;
		config.encoder = Emu.GetAudioManager().GetInfo().mode.encoder;
		config.downMixer = Emu.GetAudioManager().GetInfo().mode.downMixer;

		Memory.WriteData(config_addr, config);

		return CELL_AUDIO_OUT_SUCCEEDED;

	case CELL_AUDIO_OUT_SECONDARY:
		Memory.WriteData(config_addr, config);

		return CELL_AUDIO_OUT_SUCCEEDED;
	}

	return CELL_AUDIO_OUT_ERROR_UNSUPPORTED_AUDIO_OUT;
}

int cellAudioOutGetNumberOfDevice(u32 audioOut)
{
	cellSysutil.Warning("cellAudioOutGetNumberOfDevice(videoOut=%d)",audioOut);

	switch(audioOut)
	{
		case CELL_AUDIO_OUT_PRIMARY: return 1;
		case CELL_AUDIO_OUT_SECONDARY: return 0;
	}

	return CELL_AUDIO_OUT_ERROR_UNSUPPORTED_AUDIO_OUT;
}

int cellAudioOutGetDeviceInfo(u32 audioOut, u32 deviceIndex, mem_ptr_t<CellAudioOutDeviceInfo> info)
{
	cellSysutil.Error("Unimplemented function: cellAudioOutGetDeviceInfo(audioOut=%u, deviceIndex=%u, info_addr=0x%x)",
		audioOut, deviceIndex, info.GetAddr());

	if(deviceIndex) return CELL_AUDIO_OUT_ERROR_DEVICE_NOT_FOUND;

	info->portType = CELL_AUDIO_OUT_PORT_HDMI;
	info->availableModeCount = 1;
	info->state = CELL_AUDIO_OUT_DEVICE_STATE_AVAILABLE;
	info->latency = 1000;
	info->availableModes[0].type = CELL_AUDIO_IN_CODING_TYPE_LPCM;
	info->availableModes[0].channel = CELL_AUDIO_OUT_CHNUM_2;
	info->availableModes[0].fs = CELL_AUDIO_OUT_FS_48KHZ;
	info->availableModes[0].layout = CELL_AUDIO_OUT_SPEAKER_LAYOUT_2CH;

	return CELL_AUDIO_OUT_SUCCEEDED;
}

int cellAudioOutSetCopyControl(u32 audioOut, u32 control)
{
	cellSysutil.Warning("cellAudioOutSetCopyControl(audioOut=%d,control=%d)",audioOut,control);

	switch(audioOut)
	{
		case CELL_AUDIO_OUT_PRIMARY:
		case CELL_AUDIO_OUT_SECONDARY:
			break;

		default: return CELL_AUDIO_OUT_ERROR_UNSUPPORTED_AUDIO_OUT;
	}

	switch(control)
	{
		case CELL_AUDIO_OUT_COPY_CONTROL_COPY_FREE:
		case CELL_AUDIO_OUT_COPY_CONTROL_COPY_ONCE:
		case CELL_AUDIO_OUT_COPY_CONTROL_COPY_NEVER:
			break;

		default: return CELL_AUDIO_OUT_ERROR_ILLEGAL_PARAMETER;
	}

	return CELL_AUDIO_OUT_SUCCEEDED;
}




typedef struct{
	char cacheId[CELL_SYSCACHE_ID_SIZE];
	char getCachePath[CELL_SYSCACHE_PATH_MAX];
	mem_ptr_t<void> reserved;
} CellSysCacheParam;


class WxDirDeleteTraverser : public wxDirTraverser
{
public:
	virtual wxDirTraverseResult OnFile(const wxString& filename)
	{
		if (!wxRemoveFile(filename)){
			cellSysutil.Error("Couldn't delete File: %s", filename.wx_str());
		}
		return wxDIR_CONTINUE;
	}
	virtual wxDirTraverseResult OnDir(const wxString& dirname)
	{
		wxDir dir(dirname);
		dir.Traverse(*this);
		if (!wxRmDir(dirname)){
		//this get triggered a few times while clearing folders
		//but if this gets reimplented we should probably warn
		//if directories can't be removed
		}
		return wxDIR_CONTINUE;
	}
};

int cellSysCacheClear(void)
{
	//if some software expects CELL_SYSCACHE_ERROR_NOTMOUNTED we need to check whether
	//it was mounted before, for that we would need to save the state which I don't know
	//where to put
	wxString localPath;
	Emu.GetVFS().GetDevice(wxString("/dev_hdd1/cache/"), localPath);
	if (wxDirExists(localPath)){
		WxDirDeleteTraverser deleter;
		wxString f = wxFindFirstFile(localPath+"/*",wxDIR);
		while (!f.empty())
		{
			wxDir dir(f);
			dir.Traverse(deleter);
			f = wxFindNextFile();
		}
		return CELL_SYSCACHE_RET_OK_CLEARED;
	}
	else{
		return CELL_SYSCACHE_ERROR_ACCESS_ERROR;
	}
}

int cellSysCacheMount(mem_ptr_t<CellSysCacheParam> param)
{
	//TODO: implement
	char id[CELL_SYSCACHE_ID_SIZE];
	strncpy(id, param->cacheId, CELL_SYSCACHE_ID_SIZE);
	strncpy(param->getCachePath, ("/dev_hdd1/cache/" + std::string(id) + "/").c_str(), CELL_SYSCACHE_PATH_MAX);
	Emu.GetVFS().CreateFile(wxString(param->getCachePath));

	return CELL_SYSCACHE_RET_OK_RELAYED;
}

void cellSysutil_init()
{
	cellSysutil.AddFunc(0x40e895d3, cellSysutilGetSystemParamInt);
	cellSysutil.AddFunc(0x938013a0, cellSysutilGetSystemParamString);

	cellSysutil.AddFunc(0x887572d5, cellVideoOutGetState);
	cellSysutil.AddFunc(0xe558748d, cellVideoOutGetResolution);
	cellSysutil.AddFunc(0x0bae8772, cellVideoOutConfigure);
	cellSysutil.AddFunc(0x15b0b0cd, cellVideoOutGetConfiguration);
	cellSysutil.AddFunc(0x1e930eef, cellVideoOutGetDeviceInfo);
	cellSysutil.AddFunc(0x75bbb672, cellVideoOutGetNumberOfDevice);
	cellSysutil.AddFunc(0xa322db75, cellVideoOutGetResolutionAvailability);

	cellSysutil.AddFunc(0x189a74da, cellSysutilCheckCallback);
	cellSysutil.AddFunc(0x9d98afa0, cellSysutilRegisterCallback);
	cellSysutil.AddFunc(0x02ff3c1b, cellSysutilUnregisterCallback);

	cellSysutil.AddFunc(0x7603d3db, cellMsgDialogOpen2);
	cellSysutil.AddFunc(0x3e22cb4b, cellMsgDialogOpenErrorCode);

	cellSysutil.AddFunc(0xf4e3caa0, cellAudioOutGetState);
	cellSysutil.AddFunc(0x4692ab35, cellAudioOutConfigure);
	cellSysutil.AddFunc(0xc01b4e7c, cellAudioOutGetSoundAvailability);
	cellSysutil.AddFunc(0x2beac488, cellAudioOutGetSoundAvailability2);
	cellSysutil.AddFunc(0x7663e368, cellAudioOutGetDeviceInfo);
	cellSysutil.AddFunc(0xe5e2b09d, cellAudioOutGetNumberOfDevice);
	cellSysutil.AddFunc(0xed5d96af, cellAudioOutGetConfiguration);
	cellSysutil.AddFunc(0xc96e89e9, cellAudioOutSetCopyControl);

	cellSysutil.AddFunc(0x1e7bff94, cellSysCacheMount);
	cellSysutil.AddFunc(0x744c1544, cellSysCacheClear);

}
