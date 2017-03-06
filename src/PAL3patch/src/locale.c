#include "common.h"

// language, see patch_setlocale.c for details
unsigned system_codepage;
unsigned target_codepage;


static const wchar_t wstr_about_title_CHS[] = L"关于";
static const wchar_t wstr_about_text_CHS[] = 
    L"欢迎使用《仙剑奇侠传三》分辨率补丁 %hs\n" 
    L"\n"
    L"本补丁可以扩大游戏的分辨率\n"
    L"同时修复一些游戏程序的小问题\n"
    L"并且添加了一些实用的小功能\n" 
    L"详细信息和使用方法请参见补丁说明文件\n"
    L"\n"
    L"\n"
    L"如果您不想每次启动时看到此信息\n"
    L"请使用补丁配置工具，将“显示关于”设为“禁用”\n" 
    L"\n"
    L"\n"
    L"补丁网站:\n"
    L"  https://pal3.zbyzbyzby.com\n"
    L"\n"
    L"编译信息:\n%hs"
;

static const wchar_t wstr_confirmquit_text_CHS[] = L"您确定要退出游戏吗？\n未保存的游戏进度将会丢失。";
static const wchar_t wstr_confirmquit_title_CHS[] = L"退出";

static const wchar_t wstr_defaultfont_CHS[] = L"宋体";
static const wchar_t wstr_gameloading_CHS[] = L"游戏加载中，请稍候……";

static const wchar_t wstr_cantsavereg_text_CHS[] = L"无法保存注册表数据到存档文件夹，部分存档数据可能会丢失。\n请确认游戏对存档文件夹有可写权限。";
static const wchar_t wstr_cantsavereg_title_CHS[] = L"注册表重定向";

static const wchar_t wstr_nocfgfile_text_CHS[] = L"无法读取补丁配置文件。请运行“补丁配置工具”来生成默认配置文件。";
static const wchar_t wstr_nocfgfile_title_CHS[] = L"无法加载配置";


const wchar_t *wstr_about_title;
const wchar_t *wstr_about_text;
const wchar_t *wstr_confirmquit_text;
const wchar_t *wstr_confirmquit_title;
const wchar_t *wstr_defaultfont;
const wchar_t *wstr_gameloading;
const wchar_t *wstr_cantsavereg_text;
const wchar_t *wstr_cantsavereg_title;
const wchar_t *wstr_nocfgfile_text;
const wchar_t *wstr_nocfgfile_title;





void init_locale_early()
{
    // init codepage
    // PATCHSET 'setlocale' may overwrite target_codepage
    target_codepage = system_codepage = GetACP();
    
    // init early strings
    wstr_nocfgfile_text = wstr_nocfgfile_text_CHS;
    wstr_nocfgfile_title = wstr_nocfgfile_title_CHS;
}

void init_locale()
{
    // no translations yet
    wstr_about_title = wstr_about_title_CHS;
    wstr_about_text = wstr_about_text_CHS;
    wstr_confirmquit_text = wstr_confirmquit_text_CHS;
    wstr_confirmquit_title = wstr_confirmquit_title_CHS;
    wstr_defaultfont = wstr_defaultfont_CHS;
    wstr_gameloading = wstr_gameloading_CHS;
    wstr_cantsavereg_text = wstr_cantsavereg_text_CHS;
    wstr_cantsavereg_title = wstr_cantsavereg_title_CHS;
}
