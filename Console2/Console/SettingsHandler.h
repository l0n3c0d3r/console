#pragma once

#include "resource.h"

#include <msxml.h>

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct SettingsBase {

	virtual bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot) = 0;
	virtual bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot) = 0;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct ConsoleSettings : public SettingsBase {

	ConsoleSettings();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	wstring		strShell;
	wstring		strInitialDir;

	DWORD		dwRefreshInterval;
	DWORD		dwChangeRefreshInterval;
	DWORD		dwRows;
	DWORD		dwColumns;
	DWORD		dwBufferRows;
	DWORD		dwBufferColumns;

	COLORREF	defaultConsoleColors[16];
	COLORREF	consoleColors[16];
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct FontSettings : public SettingsBase {

	FontSettings();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	wstring		strName;
	DWORD		dwSize;
	bool		bBold;
	bool		bItalic;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

enum TransparencyStyle {

	transNone		= 0,
	transAlpha		= 1,
	transColorKey	= 2,
	transFake		= 3
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct TransparencySettings : public SettingsBase {

	TransparencySettings();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	TransparencyStyle	transStyle;
	BYTE				byActiveAlpha;
	BYTE				byInactiveAlpha;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct AppearanceSettings : public SettingsBase {

	AppearanceSettings();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	FontSettings			fontSettings;
	TransparencySettings	transparencySettings;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct HotKeys : public SettingsBase {

	HotKeys();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);


	typedef map<wstring, WORD>	CommandsMap;

	vector<ACCEL>	vecHotKeys;
	CommandsMap		mapCommands;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct TabData {

	TabData(const ConsoleSettings& conSettings)
	: strShell(conSettings.strShell)
	, strInitialDir(conSettings.strInitialDir)
	, strName(L"Console")
	, dwCursorStyle(0)
	, crCursorColor(RGB(255, 255, 255))
	, bImageBackground(false)
	, crBackgroundColor(RGB(0, 0, 0))
	, tabIcon()
	, tabBackground()
	, consoleSettings(conSettings)
	{
	}

	// custom shell settings
	wstring							strShell;
	wstring							strInitialDir;

	wstring							strName;
	DWORD							dwCursorStyle;
	COLORREF						crCursorColor;

	bool							bImageBackground;
	COLORREF						crBackgroundColor;

	CIcon							tabIcon;
	shared_ptr<ImageData>			tabBackground;

private:
	const ConsoleSettings&			consoleSettings;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

typedef vector<shared_ptr<TabData> >	TabDataVector;

struct TabSettings : public SettingsBase {

	TabSettings(const ConsoleSettings& conSettings);

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	TabDataVector	tabDataVector;

private:
	const ConsoleSettings&			consoleSettings;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

class SettingsHandler {

	public:
		SettingsHandler();
		~SettingsHandler();

	public:

		bool LoadSettings(const wstring& strOptionsFileName);

		ConsoleSettings& GetConsoleSettings() { return m_consoleSettings; }
		AppearanceSettings& GetAppearanceSettings() { return m_appearanceSettings; }
		HotKeys& GetHotKeys() { return m_hotKeys; }
		TabSettings& GetTabSettings() { return m_tabSettings; }

	private:

		CComPtr<IXMLDOMDocument>	m_pOptionsDocument;
		CComPtr<IXMLDOMElement>		m_pOptionsRoot;

	private:

		ConsoleSettings		m_consoleSettings;
		AppearanceSettings	m_appearanceSettings;
		HotKeys				m_hotKeys;

		TabSettings			m_tabSettings;
};

//////////////////////////////////////////////////////////////////////////////
