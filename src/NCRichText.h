/*---------------------------------------------------------------------\
|                                                                      |
|                      __   __    ____ _____ ____                      |
|                      \ \ / /_ _/ ___|_   _|___ \                     |
|                       \ V / _` \___ \ | |   __) |                    |
|                        | | (_| |___) || |  / __/                     |
|                        |_|\__,_|____/ |_| |_____|                    |
|                                                                      |
|                               core system                            |
|                                                        (C) SuSE GmbH |
\----------------------------------------------------------------------/

   File:       NCRichText.h

   Author:     Michael Andres <ma@suse.de>
   Maintainer: Michael Andres <ma@suse.de>

/-*/
#ifndef NCRichText_h
#define NCRichText_h

#include <iosfwd>
#include <stack>

#include "YRichText.h"
#include "NCPadWidget.h"

class NCRichText;

///////////////////////////////////////////////////////////////////
//
//	CLASS NAME : NCRichText
//
//	DESCRIPTION :
//
class NCRichText : public YRichText, public NCPadWidget {

  friend std::ostream & operator<<( std::ostream & STREAM, const NCRichText & OBJ );

  NCRichText & operator=( const NCRichText & );
  NCRichText            ( const NCRichText & );

  private:

    NCstring text;

    bool plainText;

    unsigned textwidth;
    unsigned cl;
    unsigned cc;
    unsigned cindent;
    bool     atbol;

    unsigned Tattr;

    static const unsigned Tfontmask = 0xff00;
    enum TOKEN {
      T_UNKNOWN = 0x0000,
      T_IGNORE  = 0x0001,
      T_BR      = 0x0002,
      T_PAR     = 0x0004,
      T_LEVEL   = 0x0008,
      T_LI      = 0x0010,
      // font
      T_BOLD    = 0x0100,
      T_IT      = 0x0200,
      T_TT      = 0x0400,
      T_ANC     = 0x0800,
      T_HEAD    = 0x1000
    };

  private:

    static const unsigned listindent;
    static const unsigned listindentafterlevel;
    static const string   listleveltags;

    stack<int> liststack;

    void PadChangeLevel( bool down, int tag );
    void PadSetLevel();

  private:

    class Anchor {

      public:

	static const unsigned unset = (unsigned)-1;

	unsigned sline;
	unsigned scol;
	unsigned eline;
	unsigned ecol;

	string target;

	Anchor() {
	  sline = scol = eline = ecol = unset;
	}
	Anchor( int sl, int sc ) {
	  open( sl, sc );
	}
	void open( int sl, int sc ) {
	  sline = sl;
	  scol  = sc;
	  eline = ecol = unset;
	  target = "";
	}
	void close( int el, int ec ) {
	  eline = el;
	  ecol  = ec;
	}
	bool valid() {
	  if (    sline == unset || scol == unset
	       || eline == unset || ecol == unset  )
	    return false;
	  if (    eline == sline && ecol <= scol
	       || eline < sline )
	    return false;
	  return true;
	}
	bool within( unsigned firstvisible, unsigned nextinvisible ) {
	  return sline < nextinvisible && eline >= firstvisible;
	}
	void draw( NCPad & pad, const chtype attr, int color );
    };

    static const bool showLinkTarget;

    Anchor         canchor;
    vector<Anchor> anchors;
    unsigned       armed;

    unsigned vScrollFirstvisible;
    unsigned vScrollNextinvisible;

    void openAnchor( string args );
    void closeAnchor();

    void arm( unsigned i );
    void disarm() { arm( Anchor::unset ); }

  private:

    void PadSetAttr();

    void DrawPlainPad();
    void DrawHTMLPad();

    void PadNL();
    void PadBOL();
    void PadWS( const bool tab = false );
    void PadTXT( const char * sch, const unsigned len );
    bool PadTOKEN( const char * sch, const char *& ech );

  protected:

    virtual const char * location() const { return "NCRichText"; }

    virtual void wRedraw();
    virtual void wRecoded();

    virtual NCPad * CreatePad();
    virtual void    DrawPad();

    virtual void HScroll( unsigned total, unsigned visible, unsigned start );
    virtual void VScroll( unsigned total, unsigned visible, unsigned start );

    virtual bool handleInput( int key );

  public:

    NCRichText( NCWidget * parent, YWidgetOpt & opt,
		const YCPString & text );
    virtual ~NCRichText();

    virtual long nicesize( YUIDimension dim );
    virtual void setSize( long newwidth, long newheight );

    virtual void setLabel( const YCPString & nlabel );

    virtual NCursesEvent wHandleInput( int key );

    virtual void setText( const YCPString & ntext );

    virtual bool setKeyboardFocus() {
      if ( !grabFocus() )
        return YWidget::setKeyboardFocus();
      return true;
    }
};

///////////////////////////////////////////////////////////////////

#endif // NCRichText_h