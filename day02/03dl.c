#include <stdio.h>
#include <dlfcn.h>
int main()
{
	printf("1--中文  2--english:");
	int sel;
	scanf("%d", &sel);
	void* handle;
	if(sel==1)//根据用户的选择决定加载哪个动态库
		handle = dlopen("./libch.so", RTLD_NOW);
	else
		handle = dlopen("./liben.so", RTLD_NOW);
	if(handle==NULL){//如果失败显示错误信息后退出
		puts(dlerror());
		return -1;
	}
	void (*fp)(void);
	fp = dlsym(handle, "welcome");//在库中找函数名
	if(fp==NULL){//如果失败显示错误信息后退出
		puts(dlerror());
		return -1;
	}
	fp();//(*fp)();//成功就调用这个函数
	dlclose(handle);//关闭动态库
}







