#include "time_format.h"

void SystimeToString(SYSTEMTIME* tm_, char* str_ret)
{
	sprintf(str_ret, "%d-%02d-%02d %02d:%02d:%02d:%d", 
	tm_->wYear, tm_->wMonth, tm_->wDay, tm_->wHour, tm_->wMinute, tm_->wSecond, tm_->wMilliseconds);// 时间格式化
}