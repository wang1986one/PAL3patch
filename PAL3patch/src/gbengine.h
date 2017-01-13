#ifndef PAL3PATCH_GBENGINE_H
#define PAL3PATCH_GBENGINE_H

// types

struct std_basic_string { // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char allocator;
    char *_Ptr;
    unsigned int _Len;
    unsigned int _Res;
};

struct std_vector_int {
    char allocator;
    int *_First;
    int *_Last;
    int *_End;
};

enum GAME_STATE {
    GAME_NONE,
    GAME_UI,
    GAME_SCENE,
    GAME_COMBAT,
    GAME_SUBGAME_ENCAMPMENT,
    GAME_SUBGAME_SKEE,
    GAME_HIDE_FIGHT_FIXME, // FIXME: unsure
    GAME_SUBGAME_HIDEANDSEEK,
    GAME_SUBGAME_NIGHTADVENTURE,
    GAME_OVER,
};

enum VertexProcessingType {
    SOFTWARE_VP,
    MIXED_VP,
    HARDWARE_VP,
    PURE_HARDWARE_VP
};

struct gbVec3D {
    float x;
    float y;
    float z;
};
struct gbQuaternion {
    float x;
    float y;
    float z;
    float w;
};

struct gbMatrix4 {
    union {
        struct {
            float xx;
            float xy;
            float xz;
            float xw;
            float yx;
            float yy;
            float yz;
            float yw;
            float zx;
            float zy;
            float zz;
            float zw;
            float tx;
            float ty;
            float tz;
            float tw;
        };
        float m[4][4];
    };
};


struct gbGfxDriverInfo {
    int type;
    int subtype;
    int width;
    int height;
    int colorbits;
    int depthbits;
    int stensilbits;
    int nbackbuf;
    int fullscreen;
    int refreshrate;
    char winname[0x80];
    DWORD hinst;
    HWND hgfxwnd;
    int newwindow;
    int waitforverticalblank;
};

struct CD3DEnumeration {
    IDirect3D9 *m_pD3D;
    struct CArrayList *m_pAdapterInfoList;
    char (__cdecl *ConfirmDeviceCallback)(D3DCAPS9 *, enum VertexProcessingType, D3DFORMAT, D3DFORMAT);
    unsigned int AppMinFullscreenWidth;
    unsigned int AppMinFullscreenHeight;
    unsigned int AppMinColorChannelBits;
    unsigned int AppMinAlphaChannelBits;
    unsigned int AppMinDepthBits;
    unsigned int AppMinStencilBits;
    char AppUsesDepthBuffer;
    char AppUsesMixedVP;
    char AppRequiresWindowed;
    char AppRequiresFullscreen;
    struct CArrayList *m_pAllowedAdapterFormatList;
};

struct D3DDriverBug {
    int Gamma_LowByte;
};

struct gbResManager {
    struct gbResource **pBuffer;
    int MaxNum;
    int CurNum;
};

struct gbGfxManager_D3D {
    char padding1[0xC];
    struct gbGfxDriverInfo DrvInfo;
    struct gbVertPoolMgr *pVertPoolMgr;
    struct gbEffectMgr *pEffectMgr;
    struct gbResManager *pTexResMgr;
    struct gbPrintFontMgr *pFontMgr;
    struct gbMatrixStack *pMatrixStack[0x4];
    char padding2[0x50C];
    struct CD3DEnumeration m_d3dEnumeration;
    int m_bWindowed;
    RECT m_rcWindowClient;
    RECT m_rcWindowBounds;
    ULONG m_dwWindowStyle;
    HWND m_hWnd;
    BYTE m_bMinimized;
    BYTE m_bMaximized;
    BYTE m_bClipCursorWhenFullscreen;
    BYTE m_bShowCursorWhenFullscreen;
    BYTE m_bActive;
    ULONG m_dwCreateFlags;
    struct D3DDriverBug m_DriverBug;
    struct gbResManager m_CursorMgr;
    struct gbCursorRes *m_pActiveCursor;
    int m_bShowCursor;
    char padding3[0x70];
    D3DPRESENT_PARAMETERS m_d3dpp;
    struct IDirect3D9 *m_pD3D;
    struct IDirect3DDevice9 *m_pd3dDevice;
    D3DCAPS9 m_d3dCaps;
    D3DSURFACE_DESC m_d3dsdBackBuffer;
    char m_strDeviceStats[0x5A];
    long m_ErrorCode;
    int m_bDeviceLost;
    struct IDirect3DSurface9 *m_pBackBuffer;
    int m_DXTSupported[0x5];
    struct IDirect3DVertexBuffer9 *m_pCacheVB;
    struct IDirect3DIndexBuffer9 *m_pCacheIB;
};

enum gbPixelFmtType { 
    GB_PFT_UNKNOWN,
    GB_PFT_R8G8B8,
    GB_PFT_A8R8G8B8,
    GB_PFT_R5G6B5,
    GB_PFT_A1R5G5B5,
    GB_PFT_A4R4G4B4,
    GB_PFT_P8,
    GB_PFT_A8,
    GB_PFT_X8R8G8B8,
    GB_PFT_X1R5G5B5,
    GB_PFT_X4R4G4B4,
};

struct gbSurfaceDesc {
    int width;
    int height;
    enum gbPixelFmtType format;
    int pitch;
    void *pbits;
};

struct gbTexture_D3D {
    char padding[0x54];
    struct IDirect3DBaseTexture9 *pTex;
    struct IDirect3DSurface9 *pDS;
    ULONG m_ImgFormat;
};
struct RenderTarget {
    int m_iMode;
    struct gbTexture_D3D m_Texture;
    struct gbTexture_D3D m_ScreenPlane;
    int m_nState;
};

struct gbColorQuad {
    union {
        int ColorQuadFmt;
        struct {
            BYTE Blue;
            BYTE Green;
            BYTE Red;
            BYTE Alpha;
        };
        DWORD Color;
    };
};

struct PtrArray {
    void **m_pData;
    int m_nSize;
    int m_nMaxSize;
    int m_nGrowBy;
};

struct UIWnd {
    struct UIWndVtbl *vfptr;
    struct gbColorQuad m_fontcolor;
    struct gbColorQuad m_wndcolor;
    DWORD m_id;
    RECT m_rect;
    struct UIWnd *m_pfather;
    struct PtrArray m_childs;
    int m_bcreateok;
    int m_bvisible;
    int m_benable;
    int m_bfocus;
};
struct UIWndVtbl {
    void (__fastcall *ShowWindow)(struct UIWnd *this, int dummy, int);
    void (__fastcall *Render)(struct UIWnd *this, int dummy);
    int (__fastcall *Update)(struct UIWnd *this, int dummy, float, int);
    void (__fastcall *Destroy)(struct UIWnd *this, int dummy);
    void (__fastcall *Create)(struct UIWnd *this, int dummy, unsigned int, RECT *, struct UIWnd *, char);
    void *scalar_deleting_destructor;
    int (__fastcall *OnMessage)(struct UIWnd *this, int dummy, unsigned int, unsigned int, unsigned int);
};
#define UIWnd_vfptr_Render(this) THISCALL_WRAPPER((this)->vfptr->Render, this)
#define UIWnd_vfptr_Update(this, deltatime, haveinput) THISCALL_WRAPPER((this)->vfptr->Update, this, deltatime, haveinput)

struct gbUIQuad {
    float sx;
    float sy;
    float ex;
    float ey;
    float su;
    float sv;
    float eu;
    float ev;
    float z;
    struct gbColorQuad color;
};

struct CTrail {
    float m_fTime;
    BYTE m_bSupport;
    BYTE m_bEnable;
    struct gbCamera *m_pCam;
    struct gbUIQuad m_ScreenQuad;
    ULONG m_dwRenderCounter;
    ULONG m_dwRT;
    struct gbTexture_D3D m_texRT[0x8];
    struct gbRenderEffect *m_eft;
    struct IDirect3DSurface9 *m_OriginSurface;
};


struct gbPixelFormat {
    enum gbPixelFmtType Type;
    int Bpp;
    struct gbColorQuad *Pal;
    unsigned int r_mask;
    unsigned int g_mask;
    unsigned int b_mask;
    unsigned int a_mask;
    unsigned int r_shift;
    unsigned int g_shift;
    unsigned int b_shift;
    unsigned int a_shift;
};
struct gbImage2DInfo {
    int isdiskinfo;
    int goal;
    int ngrade;
    int detail[8];
    int wdiv[8];
    int hdiv[8];
    int wrap_u;
    int wrap_v;
    int mipmap;
    int minfilter;
    int magfilter;
};
struct gbImage2D {
    struct gbImage2DInfo ImgInfo;
    int Width;
    int Height;
    struct gbPixelFormat PixelFmt;
    int BitCount;
    char *pBits;
    struct gbColorQuad *pPalette;
    int numPalEntry;
    struct gbColorQuad ColorKey;
};



struct gbVFile;
struct _iobuf;
enum ECPKMode { 
    CPKM_Null,
    CPKM_Normal,
    CPKM_FileMapping,
    CPKM_Overlapped,
    CPKM_End,
};
struct CPKHeader {
    ULONG dwLable;
    ULONG dwVersion;
    ULONG dwTableStart;
    ULONG dwDataStart;
    ULONG dwMaxFileNum;
    ULONG dwFileNum;
    ULONG dwIsFormatted;
    ULONG dwSizeOfHeader;
    ULONG dwValidTableNum;
    ULONG dwMaxTableNum;
    ULONG dwFragmentNum;
    ULONG dwPackageSize;
    ULONG dwReserved[0x14];
};
struct CPKTable {
    ULONG dwCRC;
    ULONG dwFlag;
    ULONG dwFatherCRC;
    ULONG dwStartPos;
    ULONG dwPackedSize;
    ULONG dwOriginSize;
    ULONG dwExtraInfoSize;
};
struct CPKFile {
    BYTE bValid;
    ULONG dwCRC;
    ULONG dwFatherCRC;
    int nTableIndex;
    void *lpMapAddress;
    void *lpStartAddress;
    ULONG dwOffset;
    BYTE bCompressed;
    void *lpMem;
    ULONG dwFileSize;
    ULONG dwPointer;
    struct CPKTable *pTableItem;
};
struct CPK {
    ULONG m_dwAllocGranularity;
    enum ECPKMode m_eMode;
    struct CPKHeader m_CPKHeader;
    struct CPKTable m_CPKTable[0x8000];
    struct gbVFile *m_pgbVFile[0x8];
    BYTE m_bLoaded;
    ULONG m_dwCPKHandle;
    ULONG m_dwCPKMappingHandle;
    char m_szCPKFileName[0x104];
    int m_nOpenedFileNum;
};
struct gbVFileSystem {
    int IsInit;
    char* rtDirectory;
    struct gbVFile *pFileBuffer;
    int Type;
    struct _iobuf *m_pckfp;
    DWORD m_itemcount;
    struct CPK m_cpk;
};






struct gbDynVertBuf;
struct gbRenderEffect;
struct gbTextureArray;
struct gbPrintFontMgr;

enum gbFontType {
    GB_FONT_UNICODE12,
    GB_FONT_UNICODE16,
    GB_FONT_UNICODE20,
    GB_FONT_NUMBER,
    GB_FONT_ASC,
};

struct gbPrintFont {
    struct gbPrintFontVtbl *vfptr;
    struct FontPrintInfo *ptInfo;
    struct FontSortInfoObj *pSortInfo;
    int maxInfo;
    int numInfo;
    struct FontPrint3DInfo *pt3DInfo;
    int num3DInfo;
    int max3DInfo;
    char *strBuffer;
    int maxStrBuffer;
    int curStrLoc;
    struct gbColorQuad curColor;
    float ScaleX;
    float ScaleY;
    float PitchX;
    float PitchY;
    float ZValue;
    struct gbRenderEffect *pEffect[2];
};

struct gbPrintFont_UNICODE {
    struct gbPrintFont;
    DWORD gap4C[24];
    int fontsize;
    DWORD gapB0[5];
};


struct gbBinkVideo;


struct C2DSpark_tagSpark {
    float fx;
    float fy;
    float fVx;
    float fVy;
    float fAx;
    float fAy;
    float fLum;
    float fLumInc;
    float fSize;
    float fSizeInc;
    char byColor;
    char bValid;
};

struct C2DSpark {
    struct C2DSpark_tagSpark m_Spark[512];
    float m_fDisplayWidth;
    float m_fDisplayHeight;
    int m_nCurrentSpark;
    float m_fBigLum;
    int m_nBigLumX;
    int m_nBigLumY;
    char m_bMouseTrack;
    struct gbRenderEffect *m_pAdditiveBlend;
    struct gbTexture *m_pRedBig;
    struct gbTextureArray *m_pRedBigArray;
    struct gbTexture *m_pBlue16;
    struct gbTextureArray *m_pBlue16Array;
    struct gbTexture *m_pGreen16;
    struct gbTextureArray *m_pGreen16Array;
    struct gbTexture *m_pRed16;
    struct gbTextureArray *m_pRed16Array;
    struct gbTexture *m_pYellow16;
    struct gbTextureArray *m_pYellow16Array;
    struct gbUIQuad m_Quad;
};

enum ECBShowItemKind {
    CBSIK_Null,
    CBSIK_Txt,
    CBSIK_RoleState,
    CBSIK_PrintTxt,
    CBSIK_Pic,
    CBSIK_FiveLineup,
    CBSIK_EnemyFiveLineup,
    CBSIK_CombatDialog,
    CBSIK_ScreenQuad,
    CBSIK_End,
};

struct tagShowItem {
    enum ECBShowItemKind eKind;
    char sTxt[256];
    RGBQUAD color;
    float fX;
    float fY;
    float fZ;
    float fSize;
};

struct UIStatic {
    struct UIWnd baseclass;
    int m_bordersize;
    int m_align;
    float m_ratiow;
    float m_ratioh;
    int m_textx;
    int m_texty;
    enum gbFontType m_fonttype;
    struct std_basic_string m_text;
    struct gbTexture *m_pbk;
    struct _Texture_Info *m_pbkInfo;
    struct gbTexture *m_ppic;
    struct _Texture_Info *m_ppicInfo;
    struct gbTexture *m_disablepic;
    struct _Texture_Info *m_disablepicInfo;
    struct gbTexture *m_pbk2;
    char m_mouseoff;
    int m_FVF;
    int m_nTextW;
};

struct UIFrameWnd {
    struct UIWnd baseclass;
    struct gbTexture *m_pbktex;
};

struct CCBUI;

struct CCBUI_funcptr_t {
    unsigned long (__fastcall *fp)(struct CCBUI *this, int dummy, unsigned long);
    DWORD fp_data[3];
};

struct tagUIParam {
    struct UIWnd *pUI;
    float fFromX;
    float fFromY;
    float fEndX;
    float fEndY;
    float fSpeed;
    float fEnergy;
    int nTimes;
};

struct tagUITask {
    struct CCBUI_funcptr_t fp;
    char bValid;
    char bExecuted;
    char bFinished;
    unsigned int dwID;
    float fStartTime;
    float fExpectStartTime;
    float fExpectEndTime;
    struct tagUIParam param;
    DWORD padding;
};

struct CCBUI {
    struct UIFrameWnd baseclass;
    struct UIStatic *m_pAttackSequenBack;
    struct UIStatic *m_pAttackSequenFace[11];
    struct UIStatic *m_pRoleStatePanel[4];
    struct UIStatic *m_pRoleStateFace[5];
    struct UIStatic *m_pRoleStateFaceName[5];
    union {
        struct {
            struct UIStatic *m_pRoleStateAttackInc[11];
            struct UIStatic *m_pRoleStateAttackDec[11];
            struct UIStatic *m_pRoleStateDefenceInc[11];
            struct UIStatic *m_pRoleStateDefenceDec[11];
            struct UIStatic *m_pRoleStateLuckInc[11];
            struct UIStatic *m_pRoleStateLuckDec[11];
            struct UIStatic *m_pRoleStateSpeedInc[11];
            struct UIStatic *m_pRoleStateSpeedDec[11];
            struct UIStatic *m_pRoleStateStable[11];
            struct UIStatic *m_pRoleStateBlank[11];
            struct UIStatic *m_pRoleStateForbid[11];
            struct UIStatic *m_pRoleStateSleep[11];
            struct UIStatic *m_pRoleStateChaos[11];
            struct UIStatic *m_pRoleStateMad[11];
            struct UIStatic *m_pRoleStateMirror[11];
            struct UIStatic *m_pRoleStateWall[11];
            struct UIStatic *m_pRoleStateBound[11];
            struct UIStatic *m_pRoleStateHermit[11];
            struct UIStatic *m_pRoleStateImmunity[11];
        };
        struct UIStatic *m_pRoleSpecState[19][11];
    };
    struct UIStatic *m_pWinPanel;
    struct UIStatic *m_pLosePanel;
    struct UIProgressBar *m_pRoleStateHP[4];
    struct UIProgressBar *m_pRoleStateGP[4];
    struct UIProgressBar *m_pRoleStateMP[4];
    struct UIProgressBar *m_pRoleStateSword;
    struct UIStaticCB *m_pTrickName;
    struct UIStaticCB *m_pTrickName2;
    struct UIStatic *m_pDialogBack;
    struct UIStatic *m_pResultLevelup;
    struct UIStatic *m_pResultWindLvup;
    struct UIStatic *m_pResultThunderLvup;
    struct UIStatic *m_pResultWaterLvup;
    struct UIStatic *m_pResultFireLvup;
    struct UIStatic *m_pResultEarthLvup;
    struct UIStatic *m_pResultDoubleLvup;
    struct UIStatic *m_pResultGetItem;
    struct CCBControlWindow *m_pMain;
    struct CCBItemWindow *m_pItemWindow;
    struct CCBMagicWindow *m_pMagicWindow;
    struct CCBSkillWindow *m_pSkillWindow;
    struct CCBAIWindow *m_pAIWindow;
    struct CCBLineupWindow *m_pLineupWindow;
    struct CCBProtectWindow *m_pProtectWindow;
    struct CCBResultWindow *m_pResultWindow[4];
    struct CCBSystem *m_pCBSystem;
    struct CUtil *m_pUtil;
    struct tagUITask m_Task[20];
    struct CCBUI_funcptr_t fp;
    int m_nTask;
    int m_nCurTask;
};

struct CCBLineupWindow {
    struct UIFrameWnd baseclass;
    int m_nInitRoleFaceLineup[5];
    struct UIStatic *m_pBack;
    struct UIStatic *m_pFace[5];
    int m_nSelected;
    struct CCBUI *m_pUI;
};


struct UICursor;

struct UI3DObj {
    char m_mouseoff;
    int m_enable;
    int m_needdel;
    int m_type;
    union {
        struct gbGeomNode *m_pol;
        struct Actor *m_actor;
    };
    struct gbVec3D m_pos;
};
struct UI3DCtrl {
    struct UIWnd baseclass;
    int m_numobj;
    struct UI3DObj m_obj[5];
    float m_orthosize;
    int m_rotatemode;
    char m_isrotateto;
    int m_speed;
    float m_rotate;
    float m_rotatetarget;
    float m_rotx;
    float m_rotz;
    float m_dropx;
    float m_dropy;
    float m_dropz;
    float m_scalex;
    float m_scaley;
    float m_scalez;
    struct gbLightObj *m_lightobj;
    struct gbCamera *m_camera;
    struct gbVec3D m_raydir;
};

struct gbViewPort {
    int x;
    int y;
    int width;
    int height;
    float minz;
    float maxz;
};

struct gbCamera {
    float fov;
    float OrthoSize;
    float Wscreen;
    float Hscreen;
    float zNear;
    float zFar;
    struct gbViewPort Viewport;
    float Plane[6][4];
    int numPlane;
    struct gbMatrix4 ViewMatrix;
    struct gbMatrix4 InvVMatrix;
    struct gbCamControler *pControl[16];
    int CurCtrl;
    struct gbGfxManager *pGfxMgr;
    struct gbVec3D eyeLoc;
    struct gbQuaternion eyeDir;
};

struct gbRay;

struct ObjectCamera {
    struct gbCamera *m_pCamera;
    struct gbVec3D m_camFrom;
    struct gbVec3D m_camTo;
    struct gbVec3D m_camUp;
    struct gbVec3D m_camDirect;
    float m_yaw;
    float m_pitch;
    float m_roll;
    float m_dist;
    float m_nyaw;
    float m_npitch;
    float m_nroll;
    struct gbVec3D m_forward;
    struct gbVec3D m_side;
    float m_stepRotSpeed;
    float m_stepRot;
    int m_stepRotMode;
    int m_stepRotAxis;
    char m_bStepRot;
};
struct LineupUI {
    struct UIFrameWnd baseclass;
    DWORD gapX[0x9BC2];
    struct ObjectCamera *m_pCamera;
    DWORD gapY[0xB66];
};

struct UIStaticEX {
    struct UIStatic baseclass;
    float m_rotate;
    int m_rotmode;
    float m_rotdst;
    float m_rotspeed;
    int m_rotdir;
    char m_isStoped;
    float m_accelerate;
    float m_notespeed;
};
struct UIStaticEXA {
    struct UIStaticEX baseclass;
    int center_x;
    int center_y;
};

struct PalScriptWaitObjVtbl;
struct PalScriptWaitObj {
    struct PalScriptWaitObjVtbl *vfptr;
    int m_needscriptdel;
};

struct UICaption {
    struct UIWnd baseclass;
    struct PalScriptWaitObj baseclass2;
    struct gbTexture *m_tex;
    int m_numline;
    int m_lineheight;
    int m_curline;
    float m_linetime;
};

enum UIButton_UIBUTTON_STATE {
    NORMAL = 0x0,
    MOUSEON = 0x1,
    MOUSEDOWN = 0x2,
    NUMSTATE = 0x3,
};
struct UITextureArray {
    struct gbTexture *m_ptex[16];
    int m_num;
};
struct UIButton {
    struct UIWnd baseclass;
    char m_hasDBclk;
    float m_ratiow;
    float m_ratioh;
    RECT m_drawrc;
    enum UIButton_UIBUTTON_STATE m_state;
    char m_canctrl;
    char m_bLockUpdate;
    int m_offsetx;
    int m_offsety;
    char m_bBigFont;
    struct UITextureArray m_texarray;
    struct _Texture_Info *m_texarrayInfo[3];
    struct gbTexture *m_disablepic;
    struct _Texture_Info *m_disablepicInfo;
    char m_mouseoff;
    char m_mouseon;
    int m_alignmode;
    char m_caption[128];
    char m_benable_snd;
};
struct UIDialog {
    struct UIWnd baseclass;
    int m_bmodal;
};
#define UIStaticFlex_State UIButton_UIBUTTON_STATE
struct UIStaticFlex {
    struct UIWnd baseclass;
    float DURATION;
    struct std_basic_string m_text;
    RECT m_currect;
    struct UITextureArray m_texs;
    enum UIStaticFlex_State m_state;
    float m_statetime;
    enum gbFontType m_fonttype;
    int m_tilesize;
    int m_openstyle;
};
struct UINote {
    struct UIDialog baseclass;
    struct UIStaticFlex m_static;
    float time;
};
enum UIFlexBar_STYLE {
    HORIZONTAL = 0x0,
    VERTICAL = 0x1,
};
struct UIFlexBar {
    struct UIWnd baseclass;
    int m_tilewidth;
    int m_tileheight;
    struct gbTexture *m_tex;
    enum UIFlexBar_STYLE m_style;
};
enum UIScrollBar_SB_AREA {
    UPBTN = 0x0,
    DOWNBTN = 0x1,
    SLIDER = 0x2,
    PAGEUP = 0x3,
    PAGEDOWN = 0x4,
    NONE = 0x5,
};
struct UIScrollBar {
    struct UIWnd baseclass;
    char m_bPress;
    char m_bPressed;
    struct UIFlexBar m_bk;
    int m_btnH;
    enum UIScrollBar_SB_AREA m_mouseat;
    int m_min;
    int m_max;
    int m_pos;
    int m_lastpos;
    int m_drawpos;
    int m_step;
    int m_pagesize;
    struct UITextureArray m_texarray;
    struct _Texture_Info *m_texarrayInfo[10];
    float m_keytime;
    RECT m_btnrect[2];
    int m_slideroffset;
    int m_slidertboffset;
    int m_sliderw;
    int m_sliderh;
};
struct UILBColumn {
    char head[64];
    struct PtrArray items;
    int width;
};
struct UIListBox {
    struct UIWnd baseclass;
    struct gbColorQuad m_selcolor;
    int m_showGrayBk;
    char m_hasKeyCtrl;
    struct UIScrollBar m_scrollbar;
    int m_numcol;
    struct UILBColumn m_column[8];
    int m_itemheight;
    int m_fontsize;
    int m_firstshow;
    int m_onsel;
    int m_locksel;
    RECT m_scrollRc;
    struct gbTexture *m_pbkpic;
    struct _Texture_Info *m_pbkpicInfo;
    struct gbTexture *m_selpic;
    struct _Texture_Info *m_selpicInfo;
    int m_seloffset;
    int m_seloffsetL;
    int m_seloffsetR;
    int m_scrollW;
    struct gbColorQuad m_seltexcolor;
    POINT m_itemoffset;
    int m_movesel;
    struct std_vector_int m_rowenable;
};
struct UIRoleSelect {
    struct UIDialog baseclass;
    struct PalScriptWaitObj baseclass2;
    int m_sel;
    int m_maxlen;
    struct UIListBox m_list;
    struct UIStaticFlex m_bk;
};
struct UIHeadDialog {
    struct UIDialog baseclass;
    struct PalScriptWaitObj baseclass2;
    struct Role *m_role;
    int m_width;
    int m_height;
    struct gbTexture *m_bktex;
    char m_text[256];
};
struct UIAnimateCtrl {
    struct UIWnd baseclass;
    float m_FPS;
    float m_passtime;
    struct UITextureArray m_texarray;
    int m_curframe;
    int m_numframe;
    int m_looppassed;
    int m_nLoop;
    int m_mode;
};
struct UITextArea {
    struct UIWnd baseclass;
    struct std_basic_string m_buf;
    struct std_basic_string m_page;
    char m_bInvalidate;
};
enum PGR_MODE {
    NORMAL_PGR = 0x0,
    ALPHA_PGR = 0x1,
};
struct UIProgressBar {
    struct UIWnd baseclass;
    int m_mode;
    int m_dir;
    RECT m_ProgressRc;
    RECT m_decorateRc;
    float m_progress;
    float m_speed;
    float m_SetProgress;
    float m_Lenth;
    float m_MaxVal;
    float m_stepval;
    float m_radius;
    float m_lradius;
    float m_rradius;
    float m_tradius;
    float m_bradius;
    float m_step;
    float m_Val;
    char m_IsGetit;
    struct gbColorQuad m_bkColor;
    struct gbColorQuad m_foColor;
    struct gbTexture *m_pbk;
    struct _Texture_Info *m_pbkInfo;
    struct gbTexture *m_ppic;
    struct _Texture_Info *m_ppicInfo;
    struct gbTexture *m_pdecorate;
    struct _Texture_Info *m_pdecorateInfo;
    int m_decorateW;
    int m_decorateH;
    int m_decorateOffsetX;
    int m_decorateOffsetY;
    enum PGR_MODE m_pgrmode;
    struct gbColorQuad m_color;
    int m_dstAlpha;
    int m_alpha;
    int m_minAlpha;
    float m_fadespeed;
    char m_isAdd;
    char m_isFlash;
    char m_stop;
    int m_warningval;
};
enum _FLIP {
    STATIC_LEFT_FLIP = 0x0,
    STATIC_RIGHT_FLIP = 0x1,
};
struct UIStaticFlip {
    struct UIStatic baseclass;
    enum _FLIP flipMode;
};
struct UIRoleDialog {
    struct UIDialog baseclass;
    struct PalScriptWaitObj baseclass2;
    struct UIStaticFlex m_bk;
    struct UIAnimateCtrl m_ani;
    struct UIStaticFlip m_face;
    struct UITextArea m_static;
    struct UIStatic timeclose;
    struct UIProgressBar timeprogress;
    DWORD gapX[1];
    int m_mode;
    float m_time;
    int m_sel;
};
struct ScreenEffect {
    struct PalScriptWaitObj baseclass;
    int m_blive;
    float m_life;
    float m_age;
    char m_hold;
};
enum DLG_TYPE {
    DLG_YES = 0x0,
    DLG_NO = 0x1,
    DLG_YESNO = 0x2,
    DLG_MSGBOX = 0x3,
    DLG_TYPENUM = 0x4,
};
enum DLG_MSG {
    DLG_MSG_NONE = 0xFFFFFFFF,
    DLG_BT_YES = 0x0,
    DLG_BT_NO = 0x1,
    DLG_MSG_END = 0x2,
    DLG_MSG_NUM = 0x3,
};
struct _TimeMgr {
    unsigned int newtick;
    unsigned int oldtick;
    char bNote;
};
struct MUIDialog {
    struct UIDialog baseclass_0;
    struct UIWnd *ptr_Dlg;
    unsigned int m_DlgId;
    RECT m_rect;
    RECT m_textRc;
    struct UIStaticFlex m_bk;
    struct UIStatic m_static;
    struct UIStatic m_text;
    int m_btnW;
    int m_btnH;
    RECT m_btRc;
    struct UIButton mb_Yes;
    struct UIButton mb_No;
    int Lacune;
    enum DLG_TYPE m_type;
    enum DLG_MSG m_getMsg;
    int dft_W;
    int dft_H;
    char m_IsModel;
    char m_isDoModel;
    int m_xOffset;
    int m_yOffset;
    struct _TimeMgr _m_timeMgr;
    char _m_canEndDlg;
    char _haveSound;
};
struct TimeCtl {
    unsigned int newtick;
    unsigned int oldtick;
    char bNote;
};
struct TxtFile {
    char m_token[512];
    char *m_buf;
    char *m_sectionstart;
    char *m_curpos;
};
struct ScriptData {
    unsigned __int16 m_ID;
    char m_Name[256];
    int m_RestPrice;
    char m_Rest[256];
    char m_Enough[256];
    char m_NoEnough[256];
    char m_RestEnd[256];
};
struct RestScript {
    struct TxtFile m_LoadRest;
    char m_lastFile[256];
    struct ScriptData m_Data;
};
struct UIChatRest {
    struct UIWnd baseclass;
    POINT m_pt;
    RECT rc;
    RECT bkrc;
    int m_startX;
    int m_startY;
    int mbWidth;
    int mbHeight;
    struct UIStatic m_FlagT;
    struct UIStatic m_FlagB;
    struct UIStatic m_FlagM[3];
    struct UIButton m_Chat;
    struct UIButton m_Rest;
    struct UIButton m_Exit;
    struct MUIDialog m_answerDlg;
    char m_bAnswer;
    struct ScreenEffect *eft;
    struct TimeCtl m_timewait;
    char m_isFadeOut;
    char m_isFadeIn;
    struct MUIDialog m_noenoughmsg;
    struct MUIDialog m_enough;
    struct MUIDialog m_restover;
    unsigned int m_status;
    char m_isExit;
    struct RestScript m_RestScript;
    int m_CANREST_ID;
    int m_CANNOTREST_ID;
    int m_RESTOVER_ID;
    struct PalScript *pRest;
    struct PalScript *pCantRest;
    struct PalScript *pRestOver;
    char m_bActive;
};
enum PAL3_FRAME {
    FRM_SCENE = 0x0,
    // many values unknown
};
enum UIEMOTE {
    EM_NONE = 0x0,
    EM_SHUI = 0x1,
    EM_JING = 0x2,
    EM_YI = 0x3,
    EM_NU = 0x4,
    EM_XI = 0x5,
    EM_XIN = 0x6,
    EM_HAN = 0x7,
    EM_LUAN = 0x8,
    EM_JI = 0x9,
    EM_QI = 0xA,
    EM_YUN = 0xB,
    EM_SHENG = 0xC,
    EM_BEI = 0xD,
    EM_NUM = 0xE,
};
struct UIEmote {
    struct UIWnd baseclass;
    struct PalScriptWaitObj baseclass2;
    enum UIEMOTE m_cur;
    struct UIAnimateCtrl m_ani[13];
    struct Role *m_role;
    int m_loopcount;
    int m_nLoop[13];
};
struct UIGameFrm {
    struct UIWnd baseclass_0;
    BYTE gap0[192];
    struct UICaption m_cap;
    struct UINote m_note;
    unsigned int m_SmeltChatScript;
    unsigned int m_HockShopScript;
    unsigned int m_EncampFlag;
    unsigned int m_ExitRow;
    char m_SDTY;
    char m_APPR;
    char m_SKEE;
    unsigned int m_ExitSkee;
    struct ScreenEffect *eft;
    char m_isFadeOut;
    char m_overFade;
    struct UIRoleSelect m_seldlg;
    struct UIHeadDialog m_headdlg[5];
    struct UIRoleDialog m_roledlg;
    struct UIChatRest m_ChatRest;
    unsigned int m_ChatRestStatus;
    struct UIFrameWnd *m_curfrm;
    enum PAL3_FRAME m_curfrmid;
    enum PAL3_FRAME m_lastfrmid;
    struct UIEmote m_emote[6];
    struct UISceneFrm *m_scenefrm;
    struct StateUI *m_sysfrm;
    struct ChoseCompose *m_chosecompose;
};
struct UISceneMap {
    struct UIWnd baseclass;
    struct UIButton m_probe;
    struct UIStatic m_base;
    struct UIStaticEX m_compass;
    struct UIStaticFlex m_mapbk;
    struct UITextureArray m_icons;
    int m_state;
};
struct UISceneFace {
    struct UIWnd baseclass;
    struct UIProgressBar m_hp;
    struct UIProgressBar m_mp;
    struct UIStatic m_face[3];
    struct UIStatic m_bk;
    float m_clicktime;
    int m_onclick;
    struct UIStatic m_state[4];
};
struct UISceneFrm {
    struct UIFrameWnd baseclass;
    struct UISceneMap m_map;
    struct UISceneFace m_face;
};

// functions
#define gbGfxManager_D3D_Reset3DEnvironment(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x1001AC50, int, struct gbGfxManager_D3D *), this)
#define gbGfxManager_D3D_BuildPresentParamsFromSettings(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x1001A190, void, struct gbGfxManager_D3D *), this)
#define gbGfxManager_D3D_EndScene(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x10018F00, void, struct gbGfxManager_D3D *), this)
extern enum gbPixelFmtType gbGfxManager_D3D_GetBackBufferFormat(struct gbGfxManager_D3D *this);
extern void gbGfxManager_D3D_EnsureCooperativeLevel(struct gbGfxManager_D3D *this, int requirefocus);
#define UIWnd_SetRect(this, rect) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00445FA0, void, struct UIWnd *, RECT *), this, rect)
#define gbTexture_D3D_CreateForRenderTarget(this, width, height, format) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x1001BF80, int, struct gbTexture_D3D *, int, int, enum gbPixelFmtType), this, width, height, format)
#define gbTexture_D3D_CreateFromFileMemory(this, data, len) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x1001C010, void, struct gbTexture_D3D *, void *, int), this, data, len)
#define gbPrintFontMgr_GetFont(this, fonttype) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x10004450, struct gbPrintFont *, struct gbPrintFontMgr *, enum gbFontType), this, fonttype)
#define gbPrintFont_PrintString(this, str, x, y, endx, endy) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x10022BF0, void, struct gbPrintFont *, const char *, float, float, float, float), this, str, x, y, endx, endy)
#define gbmalloc ((malloc_funcptr_t) (gboffset + 0x100E4B0D))
#define gbfree ((free_funcptr_t) (gboffset + 0x100E4B99))
#define gbx2x(gbx) (((gbx) + 1.0) * PAL3_s_drvinfo.width / 2.0)
#define gby2y(gby) ((1.0 - (gby)) * PAL3_s_drvinfo.height / 2.0)
#define x2gbx(x) ((x) * 2.0 / PAL3_s_drvinfo.width - 1.0)
#define y2gby(y) (1.0 - (y) * 2.0 / PAL3_s_drvinfo.height)
#define gbCamera_SetAsCurrent(this, a2) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x10021A80, void, struct gbCamera *, int), this, a2)
#define gbCamera_PointEyeToScr_100220B0(this, a2, a3, a4) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x100220B0, void, struct gbCamera *, struct gbVec3D *, float *, float *), this, a2, a3, a4)
#define gbCamera_GetRayToScreen(this, a2, a3, a4) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x100222C0, void, struct gbCamera *, float, float, struct gbRay *), this, a2, a3, a4);
#define gbMatrixStack_Scale(this, a2, a3, a4) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(gboffset + 0x10027520, void, struct gbMatrixStack *, float, float, float), this, a2, a3, a4);

// PAL3 functions
#define PrepareDir ((int (*)(void)) TOPTR(0x00538320))
#define gbBinkVideo_Width(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0053C710, int, struct gbBinkVideo *), this)
#define gbBinkVideo_Height(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0053C720, int, struct gbBinkVideo *), this)
#define gbBinkVideo_DrawFrameEx(this, pDestBuf, nDestPitch, nDestHeight, nDestLeft, nDestTop, nDestSurfaceType) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0053C530, int, struct gbBinkVideo *, void *, int, int, int, int, int), this, pDestBuf, nDestPitch, nDestHeight, nDestLeft, nDestTop, nDestSurfaceType)
#define PAL3_InitGFX ((void (*)(void)) TOPTR(0x00404FF0))
#define UIDrawTextEx ((void (*)(const char *, RECT *, struct gbPrintFont *, int, int)) TOPTR(0x00541210))
#define UIPrint ((void (*)(int, int, char *, struct gbColorQuad *, int)) TOPTR(0x00540FD0))
#define C2DSpark_Render(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x004D61C0, void, struct C2DSpark *), this)
#define C2DSpark_CreateSingle(this, pSpark) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x004D5EC0, bool, struct C2DSpark *, struct C2DSpark_tagSpark *), this, pSpark)
#define C2DSpark_CreateStars(this, x, y, nWidth, fStarSize) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x004D6050, void, struct C2DSpark *, int, int, int, float), this, x, y, nWidth, fStarSize)
#define CCBUI_Create(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x005163D0, bool, struct CCBUI *), this)
#define UIFrameWnd_Render(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0043DDF0, void, struct UIFrameWnd *), this)
#define UIWnd_Create(this, id, rect, pfather) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00445B90, void, struct UIWnd *, int, RECT *, struct UIWnd *), this, id, rect, pfather)
#define UIWnd_MoveWindow(this, x, y) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00445D20, void, struct UIWnd *, int, int), this, x, y)
#define UICursor_IRender(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00541640, void, struct UICursor *), this)
#define UI3DCtrl_SetOriginPt_XY(this, x, y) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00439850, void, struct UI3DCtrl *, int, int), this, x, y)
#define UI3DCtrl_SetOriginPt_XYFromY(this, x, y, from_y) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00439930, void, struct UI3DCtrl *, int, int, int), this, x, y, from_y)
#define UI3DCtrl_Render(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00439410, void, struct UI3DCtrl *), this)
#define UI3DCtrl_Update(this, deltatime, haveinput) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00439A20, int, struct UI3DCtrl *, float, int), this, deltatime, haveinput)
#define UI3DCtrl_GetMouseRay(this, mray, cursorpt) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00439FE0, struct gbRay *, struct UI3DCtrl *, struct gbRay *, POINT *), this, mray, cursorpt)
#define LineupUI_Create(this, pWnd) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00483650, void, struct LineupUI *, struct UIWnd *), this, pWnd)
#define UIStaticEX_Render(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00442E90, void, struct UIStaticEX *), this)
#define UIStaticEXA_Render(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00443200, void, struct UIStaticEXA *), this)
#define UIGameFrm_Create(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0044F130, void, struct UIGameFrm *), this)
#define PlayerMgr_Create ((void (*)(void)) TOPTR(0x00408BE0))
#define PlayerMgr_DrawMsg ((void (*)(void)) TOPTR(0x0040C7D0))
#define UIAnimateCtrl_Render(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x0043A270, void, struct UIAnimateCtrl *), this)
#define UIWnd_Render_rewrited(this) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00445CD0, void, struct UIWnd *), this)
#define UIRoleDialog_Create(this, id, rect, pfather, bkfile) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00450F90, void, struct UIRoleDialog *, int, RECT *, struct UIWnd *, const char *), this, id, rect, pfather, bkfile)
#define UIRoleDialog_SetFace(this, path, leftright) THISCALL_WRAPPER(MAKE_THISCALL_FUNCPTR(0x00451360, void, struct UIRoleDialog *, const char *, int), this, path, leftright)

// global variables
#define GB_GfxMgr (*(struct gbGfxManager_D3D **) 0x00BFDA60)
#define g_msgbk (*(struct UIStaticFlex *) TOPTR(0x00BFDAB0))
#define PAL3_s_gamestate (*(int *) TOPTR(0x00BFDA6C))
#define PAL3_s_drvinfo (*(struct gbGfxDriverInfo *) TOPTR(0x00BFD6C8))
#define PAL3_s_bActive (*(int *) TOPTR(0x005833B8))
#define PAL3_s_flag (*(int *) TOPTR(0x005833BC))
#define g_pVFileSys (*(struct gbVFileSystem **) (gboffset + 0x1015D3A8))

#endif
