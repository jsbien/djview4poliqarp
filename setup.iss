; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!
; This is the Inno Setup script for Chess Explorer.
; Inno Setup creates install files for MS Windows.

#define MyAppName "DjView4Poliqarp"
#define MyAppVerName "DjView4Poliqarp-1.2"
#define MyAppPublisher "Michal Rudolf"
#define MyAppUrl "http://bitbucket.org/mrudolf/djview-poliqarp"
#define MyAppExeName "djview4poliqarp.exe"

[Setup]
AppName={#MyAppName}
AppVerName={#MyAppVerName}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputBaseFilename={#MyAppVerName}
Compression=lzma/ultra
InternalCompressLevel=ultra
SolidCompression=true
OutputDir=.

[Languages]
Name: "eng"; MessagesFile: "compiler:Default.isl"
Name: brazilianportuguese; MessagesFile: compiler:Languages\BrazilianPortuguese.isl
Name: czech; MessagesFile: compiler:Languages\Czech.isl
Name: dutch; MessagesFile: compiler:Languages\Dutch.isl
Name: french; MessagesFile: compiler:Languages\French.isl
Name: german; MessagesFile: compiler:Languages\German.isl
Name: hungarian; MessagesFile: compiler:Languages\Hungarian.isl
Name: italian; MessagesFile: compiler:Languages\Italian.isl
Name: norwegian; MessagesFile: compiler:Languages\Norwegian.isl
Name: polish; MessagesFile: compiler:Languages\Polish.isl
Name: spanish; MessagesFile: compiler:Languages\Spanish.isl

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "H:\programming\build\djview4poliqarp-windows\Release\djview4poliqarp.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "H:\programming\build\djview4poliqarp-windows\Release\libdjvulibre-21.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\windows\system\mingwm10.dll"; DestDir: "{app}";
Source: "C:\windows\system\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\windows\system\QtCore4.dll"; DestDir: "{app}";
Source: "C:\windows\system\QtGui4.dll"; DestDir: "{app}";
Source: "C:\windows\system\QtOpenGl4.dll"; DestDir: "{app}";
Source: "C:\windows\system\QtXml4.dll"; DestDir: "{app}";
Source: "C:\windows\system\QtNetwork4.dll"; DestDir: "{app}";
Source: "C:\windows\system\imageformats\qjpeg4.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion

; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{userdesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"; Tasks: quicklaunchicon

[Run]
Filename: {app}\{#MyAppExeName}; Description: {cm:LaunchProgram,{#MyAppName}}; Flags: nowait postinstall skipifsilent
