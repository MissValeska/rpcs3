#pragma once

struct DbgPacket
{
	int m_ch;
	wxString m_text;

	DbgPacket(int ch, const wxString& text)
		: m_ch(ch)
		, m_text(text)
	{
	}

	DbgPacket()
	{
	}

	void Clear()
	{
		m_text.Clear();
	}
};

struct _DbgBuffer : public MTPacketBuffer<DbgPacket>
{
	_DbgBuffer() : MTPacketBuffer<DbgPacket>(1024)
	{
	}

	void _push(const DbgPacket& data)
	{
		const u32 stext = data.m_text.Len();

		m_buffer.Reserve(sizeof(int) + sizeof(u32) + stext);

		u32 c_put = m_put;

		memcpy(&m_buffer[c_put], &data.m_ch, sizeof(int));
		c_put += sizeof(int);

		memcpy(&m_buffer[c_put], &stext, sizeof(u32));
		c_put += sizeof(u32);
		memcpy(&m_buffer[c_put], static_cast<const char *>(data.m_text), stext);
		c_put += stext;

		m_put = c_put;
		CheckBusy();
	}

	DbgPacket _pop()
	{
		DbgPacket ret;

		u32 c_get = m_get;

		ret.m_ch = *(int*)&m_buffer[c_get];
		c_get += sizeof(int);

		const u32& stext = *(u32*)&m_buffer[c_get];
		c_get += sizeof(u32);
		if (stext) ret.m_text = wxString(reinterpret_cast<const char*>(&m_buffer[c_get]), stext );
		c_get += stext;

		m_get = c_get;
		if(!HasNewPacket()) Flush();

		return ret;
	}
};

class DbgConsole
	: public FrameBase
	, public ThreadBase
{
	wxFile* m_output;
	wxTextCtrl* m_console;
	wxTextAttr* m_color_white;
	wxTextAttr* m_color_red;
	_DbgBuffer m_dbg_buffer;

public:
	DbgConsole();
	~DbgConsole();
	void Write(int ch, const wxString& text);
	void Clear();
	virtual void Task();

private:
	void OnQuit(wxCloseEvent& event);
	DECLARE_EVENT_TABLE();
};