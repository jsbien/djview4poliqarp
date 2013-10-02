; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{BAC356C7-9445-0012-3BF5-A3919C9E4A91}
AppName=DjView for Poliqarp
AppVerName=DjView for Poliqarp 1.2
DefaultDirName={pf}\DjView4Poliqarp
DefaultGroupName=DjView for Poliqarp
OutputBaseFilename=djview4poliqarp-setup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "polish"; MessagesFile: "compiler:Languages\Polish.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "H:\programming\build\djview4poliqarp-windows\release\djview4poliqarp.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "Q:\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Q:\mingwm10.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "H:\programming\build\djview4poliqarp-windows\release\libdjvulibre-21.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Q:\QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Q:\QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Q:\QtXml4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Q:\QtNetwork4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Q:\imageformats\qjpeg4.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\DjView for Poliqarp"; Filename: "{app}\djview4poliqarp.exe"
Name: "{group}\{cm:UninstallProgram,DjView for Poliqarp}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\DjView for Poliqarp"; Filename: "{app}\djview4poliqarp.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\djview4poliqarp.exe"; Description: "{cm:LaunchProgram,DjView for Poliqarp}"; Flags: nowait postinstall skipifsilent




