; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "JobAccounting"
#define MyAppVersion "1.0"
#define MyAppPublisher "masterarrow"
#define MyAppURL "masterarrows@gmail.com"
#define MyAppExeName "JobAccounting.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{5A9210E8-4D11-4D43-9FE4-8D9A4D0D63C8}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\Job Accounting
DisableProgramGroupPage=yes
OutputDir=D:\Install\Projects\GitHub\QtProjects\JobAccounting\Installer
OutputBaseFilename=JobAccounting
SetupIconFile=D:\Install\Projects\GitHub\QtProjects\JobAccounting\JobAccounting\res\JobAccounting.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "ukrainian"; MessagesFile: "compiler:Languages\Ukrainian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\JobAccounting.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\iconengines\*"; DestDir: "{app}\iconengines"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\imageformats\*"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\platforms\*"; DestDir: "{app}\platforms\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\sqldrivers\*"; DestDir: "{app}\sqldrivers"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\styles\*"; DestDir: "{app}\styles"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\translations\*"; DestDir: "{app}\translations"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\D3Dcompiler_47.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\JobAccounting.exe.manifest"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\libEGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\libGLESV2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\opengl32sw.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\qt.conf"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\Qt5Sql.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\Qt5Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Install\Projects\GitHub\QtProjects\JobAccounting\Windows\MSVC\Release\settings.ini"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
