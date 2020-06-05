#pragma once

#define FN_ENUM_TO_STRING(x) #x
/**
@struct	OpenCL Error code Enum
@brief	
@remark	
-	
@author	선경규(Kyeong Kyu - Seon)
@date	2019/5/8  8:57
*/
enum enOCLErr
{
	CL_SUCCESS = 0,
	CL_DEVICE_NOT_FOUND = -1,
	CL_DEVICE_NOT_AVAILABLE = -2,
	CL_COMPILER_NOT_AVAILABLE = -3,
	CL_MEM_OBJECT_ALLOCATION_FAILURE = -4,
	CL_OUT_OF_RESOURCES = -5,
	CL_OUT_OF_HOST_MEMORY = -6,
	CL_PROFILING_INFO_NOT_AVAILABLE = -7,
	CL_MEM_COPY_OVERLAP = -8,
	CL_IMAGE_FORMAT_MISMATCH = -9,
	CL_IMAGE_FORMAT_NOT_SUPPORTED = -10,
	CL_BUILD_PROGRAM_FAILURE = -11,
	CL_MAP_FAILURE = -12,
	CL_MISALIGNED_SUB_BUFFER_OFFSET = -13,
	CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST = -14,
	CL_COMPILE_PROGRAM_FAILURE = -15,
	CL_LINKER_NOT_AVAILABLE = -16,
	CL_LINK_PROGRAM_FAILURE = -17,
	CL_DEVICE_PARTITION_FAILED = -18,
	CL_KERNEL_ARG_INFO_NOT_AVAILABLE = -19,

	CL_INVALID_VALUE = -30,
	CL_INVALID_DEVICE_TYPE = -31,
	CL_INVALID_PLATFORM = -32,
	CL_INVALID_DEVICE = -33,
	CL_INVALID_CONTEXT = -34,
	CL_INVALID_QUEUE_PROPERTIES = -35,
	CL_INVALID_COMMAND_QUEUE = -36,
	CL_INVALID_HOST_PTR = -37,
	CL_INVALID_MEM_OBJECT = -38,
	CL_INVALID_IMAGE_FORMAT_DESCRIPTOR = -39,
	CL_INVALID_IMAGE_SIZE = -40,
	CL_INVALID_SAMPLER = -41,
	CL_INVALID_BINARY = -42,
	CL_INVALID_BUILD_OPTIONS = -43,
	CL_INVALID_PROGRAM = -44,
	CL_INVALID_PROGRAM_EXECUTABLE = -45,
	CL_INVALID_KERNEL_NAME = -46,
	CL_INVALID_KERNEL_DEFINITION = -47,
	CL_INVALID_KERNEL = -48,
	CL_INVALID_ARG_INDEX = -49,
	CL_INVALID_ARG_VALUE = -50,
	CL_INVALID_ARG_SIZE = -51,
	CL_INVALID_KERNEL_ARGS = -52,
	CL_INVALID_WORK_DIMENSION = -53,
	CL_INVALID_WORK_GROUP_SIZE = -54,
	CL_INVALID_WORK_ITEM_SIZE = -55,
	CL_INVALID_GLOBAL_OFFSET = -56,
	CL_INVALID_EVENT_WAIT_LIST = -57,
	CL_INVALID_EVENT = -58,
	CL_INVALID_OPERATION = -59,
	CL_INVALID_GL_OBJECT = -60,
	CL_INVALID_BUFFER_SIZE = -61,
	CL_INVALID_MIP_LEVEL = -62,
	CL_INVALID_GLOBAL_WORK_SIZE = -63,
	CL_INVALID_PROPERTY = -64,
	CL_INVALID_IMAGE_DESCRIPTOR = -65,
	CL_INVALID_COMPILER_OPTIONS = -66,
	CL_INVALID_LINKER_OPTIONS = -67,
	CL_INVALID_DEVICE_PARTITION_COUNT = -68
};

// 
inline void _in_fn_Uni2Multi(const wchar_t* InputString, char* OutString)
{
	//if (wcslen(InputString) <= sizeof(wchar_t) * strlen(OutString))
	if (wcslen(InputString) > 0 && wcslen(InputString) < 1024)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, InputString, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, InputString, -1, OutString, len, NULL, NULL);
	}
	else
	{
		OutputDebugString(_T("InputString Length Error."));
	}
}

/**
@brief	MultiByte to Unicode
@return	유니코드 문자열
@param	멀티바이트 문자열
@remark
- Multibyte를 Unicode로 변환하는 함수.
@author	선경규(Kyeong Kyu - Seon)
@date	2018/4/24  13:19
*/
inline void _in_fn_Multi2Uni(const char* InputString, wchar_t* OutString)
{
	//if (strlen(InputString) < sizeof(char) * wcslen(OutString))
	if(strlen(InputString) > 0 && strlen(InputString) < 1024)
	{
		static wchar_t strUnicode[1024] = { 0, };
		int nLen = MultiByteToWideChar(CP_ACP, 0, InputString, (int)strlen(InputString), NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, InputString, (int)strlen(InputString), OutString, nLen);
	}
	else
	{
		OutputDebugString(_T("InputString Length Error."));
	}
}

inline void _in_fn_Multi2Uni_UTF8(const char* InputString, wchar_t* OutString)
{
	//if (strlen(InputString) < sizeof(char) * wcslen(OutString))
	if (strlen(InputString) > 0 && strlen(InputString) < 1024)
	{
		static wchar_t strUnicode[1024] = { 0, };
		int nLen = MultiByteToWideChar(CP_UTF8, 0, InputString, (int)strlen(InputString), NULL, NULL);
		MultiByteToWideChar(CP_UTF8, 0, InputString, (int)strlen(InputString), OutString, nLen);
	}
	else
	{
		OutputDebugString(_T("InputString Length Error."));
	}
}

inline void _in_fn_Wstr2Str(std::wstring& wstr, std::string& str)
{
	str.assign(wstr.begin(), wstr.end());
}

inline void _in_fn_Str2Wstr(std::string& str, std::wstring& wstr)
{
	wstr.assign(str.begin(), str.end());
}
// 
// inline CString g_fnGetErrorMsg()
// {
// 	LPVOID lpMsgBuf;
// 	CString strErrorMessage;
// 	DWORD dw = GetLastError();
// 	DWORD error =
// 		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
// 			NULL,
// 			dw,
// 			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
// 			(LPTSTR)&lpMsgBuf,
// 			0,
// 			NULL);
// 	strErrorMessage.Format(TEXT("[%d] %s"), dw, lpMsgBuf);
// 	OutputDebugString(strErrorMessage);
// 	LocalFree(lpMsgBuf);
// 	return strErrorMessage;
// }

inline std::string g_fn_GetOCLErrorString(int nErr)
{
	enOCLErr enErr = static_cast<enOCLErr>(nErr);
	std::string strRtn = "";
	switch (enErr)
	{
	case enOCLErr::CL_SUCCESS:
		strRtn = "CL_SUCCESS";
		break;
	case enOCLErr::CL_DEVICE_NOT_FOUND:
		strRtn = "CL_DEVICE_NOT_FOUND";
		break;
	case enOCLErr::CL_DEVICE_NOT_AVAILABLE:
		strRtn = "CL_DEVICE_NOT_AVAILABLE";
		break;
	case enOCLErr::CL_COMPILER_NOT_AVAILABLE:
		strRtn = "CL_COMPILER_NOT_AVAILABLE";
		break;
	case enOCLErr::CL_MEM_OBJECT_ALLOCATION_FAILURE:
		strRtn = "CL_MEM_OBJECT_ALLOCATION_FAILURE";
		break;
	case enOCLErr::CL_OUT_OF_RESOURCES:
		strRtn = "CL_OUT_OF_RESOURCES";
		break;
	case enOCLErr::CL_OUT_OF_HOST_MEMORY:
		strRtn = "CL_OUT_OF_HOST_MEMORY";
		break;
	case enOCLErr::CL_PROFILING_INFO_NOT_AVAILABLE:
		strRtn = "CL_PROFILING_INFO_NOT_AVAILABLE";
		break;
	case enOCLErr::CL_MEM_COPY_OVERLAP:
		strRtn = "CL_MEM_COPY_OVERLAP";
		break;
	case enOCLErr::CL_IMAGE_FORMAT_MISMATCH:
		strRtn = "CL_IMAGE_FORMAT_MISMATCH";
		break;
	case enOCLErr::CL_IMAGE_FORMAT_NOT_SUPPORTED:
		strRtn = "CL_IMAGE_FORMAT_NOT_SUPPORTED";
		break;
	case enOCLErr::CL_BUILD_PROGRAM_FAILURE:
		strRtn = "CL_BUILD_PROGRAM_FAILURE";
		break;
	case enOCLErr::CL_MAP_FAILURE:
		strRtn = "CL_MAP_FAILURE";
		break;
	case enOCLErr::CL_MISALIGNED_SUB_BUFFER_OFFSET:
		strRtn = "CL_MISALIGNED_SUB_BUFFER_OFFSET";
		break;
	case enOCLErr::CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
		strRtn = "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
		break;
	case enOCLErr::CL_COMPILE_PROGRAM_FAILURE:
		strRtn = "CL_COMPILE_PROGRAM_FAILURE";
		break;
	case enOCLErr::CL_LINKER_NOT_AVAILABLE:
		strRtn = "CL_LINKER_NOT_AVAILABLE";
		break;
	case enOCLErr::CL_LINK_PROGRAM_FAILURE:
		strRtn = "CL_LINK_PROGRAM_FAILURE";
		break;
	case enOCLErr::CL_DEVICE_PARTITION_FAILED:
		strRtn = "CL_DEVICE_PARTITION_FAILED";
		break;
	case enOCLErr::CL_KERNEL_ARG_INFO_NOT_AVAILABLE:
		strRtn = "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";
		break;
	case enOCLErr::CL_INVALID_VALUE:
		strRtn = "CL_INVALID_VALUE";
		break;
	case enOCLErr::CL_INVALID_DEVICE_TYPE:
		strRtn = "CL_INVALID_DEVICE_TYPE";
		break;
	case enOCLErr::CL_INVALID_PLATFORM:
		strRtn = "CL_INVALID_PLATFORM";
		break;
	case enOCLErr::CL_INVALID_DEVICE:
		strRtn = "CL_INVALID_DEVICE";
		break;
	case enOCLErr::CL_INVALID_CONTEXT:
		strRtn = "CL_INVALID_CONTEXT";
		break;
	case enOCLErr::CL_INVALID_QUEUE_PROPERTIES:
		strRtn = "CL_INVALID_QUEUE_PROPERTIES";
		break;
	case enOCLErr::CL_INVALID_COMMAND_QUEUE:
		strRtn = "CL_INVALID_COMMAND_QUEUE";
		break;
	case enOCLErr::CL_INVALID_HOST_PTR:
		strRtn = "CL_INVALID_HOST_PTR";
		break;
	case enOCLErr::CL_INVALID_MEM_OBJECT:
		strRtn = "CL_INVALID_MEM_OBJECT";
		break;
	case enOCLErr::CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
		strRtn = "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
		break;
	case enOCLErr::CL_INVALID_IMAGE_SIZE:
		strRtn = "CL_INVALID_IMAGE_SIZE";
		break;
	case enOCLErr::CL_INVALID_SAMPLER:
		strRtn = "CL_INVALID_SAMPLER";
		break;
	case enOCLErr::CL_INVALID_BINARY:
		strRtn = "CL_INVALID_BINARY";
		break;
	case enOCLErr::CL_INVALID_BUILD_OPTIONS:
		strRtn = "CL_INVALID_BUILD_OPTIONS";
		break;
	case enOCLErr::CL_INVALID_PROGRAM:
		strRtn = "CL_INVALID_PROGRAM";
		break;
	case enOCLErr::CL_INVALID_PROGRAM_EXECUTABLE:
		strRtn = "CL_INVALID_PROGRAM_EXECUTABLE";
		break;
	case enOCLErr::CL_INVALID_KERNEL_NAME:
		strRtn = "CL_INVALID_KERNEL_NAME";
		break;
	case enOCLErr::CL_INVALID_KERNEL_DEFINITION:
		strRtn = "CL_INVALID_KERNEL_DEFINITION";
		break;
	case enOCLErr::CL_INVALID_KERNEL:
		strRtn = "CL_INVALID_KERNEL";
		break;
	case enOCLErr::CL_INVALID_ARG_INDEX:
		strRtn = "CL_INVALID_ARG_INDEX";
		break;
	case enOCLErr::CL_INVALID_ARG_VALUE:
		strRtn = "CL_INVALID_ARG_VALUE";
		break;
	case enOCLErr::CL_INVALID_ARG_SIZE:
		strRtn = "CL_INVALID_ARG_SIZE";
		break;
	case enOCLErr::CL_INVALID_KERNEL_ARGS:
		strRtn = "CL_INVALID_KERNEL_ARGS";
		break;
	case enOCLErr::CL_INVALID_WORK_DIMENSION:
		strRtn = "CL_INVALID_WORK_DIMENSION";
		break;
	case enOCLErr::CL_INVALID_WORK_GROUP_SIZE:
		strRtn = "CL_INVALID_WORK_GROUP_SIZE";
		break;
	case enOCLErr::CL_INVALID_WORK_ITEM_SIZE:
		strRtn = "CL_INVALID_WORK_ITEM_SIZE";
		break;
	case enOCLErr::CL_INVALID_GLOBAL_OFFSET:
		strRtn = "CL_INVALID_GLOBAL_OFFSET";
		break;
	case enOCLErr::CL_INVALID_EVENT_WAIT_LIST:
		strRtn = "CL_INVALID_EVENT_WAIT_LIST";
		break;
	case enOCLErr::CL_INVALID_EVENT:
		strRtn = "CL_INVALID_EVENT";
		break;
	case enOCLErr::CL_INVALID_OPERATION:
		strRtn = "CL_INVALID_OPERATION";
		break;
	case enOCLErr::CL_INVALID_GL_OBJECT:
		strRtn = "CL_INVALID_GL_OBJECT";
		break;
	case enOCLErr::CL_INVALID_BUFFER_SIZE:
		strRtn = "CL_INVALID_BUFFER_SIZE";
		break;
	case enOCLErr::CL_INVALID_MIP_LEVEL:
		strRtn = "CL_INVALID_MIP_LEVEL";
		break;
	case enOCLErr::CL_INVALID_GLOBAL_WORK_SIZE:
		strRtn = "CL_INVALID_GLOBAL_WORK_SIZE";
		break;
	case enOCLErr::CL_INVALID_PROPERTY:
		strRtn = "CL_INVALID_PROPERTY";
		break;
	case enOCLErr::CL_INVALID_IMAGE_DESCRIPTOR:
		strRtn = "CL_INVALID_IMAGE_DESCRIPTOR";
		break;
	case enOCLErr::CL_INVALID_COMPILER_OPTIONS:
		strRtn = "CL_INVALID_COMPILER_OPTIONS";
		break;
	case enOCLErr::CL_INVALID_LINKER_OPTIONS:
		strRtn = "CL_INVALID_LINKER_OPTIONS";
		break;
	case enOCLErr::CL_INVALID_DEVICE_PARTITION_COUNT:
		strRtn = "CL_INVALID_DEVICE_PARTITION_COUNT";
		break;
	}
	strRtn.insert(0, "OCL ERR CODE : ");
	return strRtn;
}
