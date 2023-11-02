#include <Windows.h>

bool changeFlushRateA(int flushRate) {
	//初始化DEVMODE
	DEVMODE modea;
	modea.dmSize = sizeof(modea);

	//获取当前显示配置
	//仅针对单显示器（垃圾学校电脑只有一个显示器所以没适配多显示器）
	EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &modea);

	if (flushRate <= 0) {
		return false;
	}

	modea.dmDisplayFrequency = flushRate;

	if (ChangeDisplaySettings(&modea, 0) == DISP_CHANGE_SUCCESSFUL) {
		return true;
	}

	return false;
}

bool changeFlushRateB(DEVMODE devMode) {
	//判断dmSize是否定义
	if (devMode.dmSize == NULL) {
		return false;
	}

	if (devMode.dmDisplayFrequency <= 0) {
		return false;
	}

	if (ChangeDisplaySettings(&devMode, 0) == DISP_CHANGE_SUCCESSFUL) {
		return true;
	}
	return false;
}