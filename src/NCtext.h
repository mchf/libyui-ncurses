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

   File:       NCtext.h

   Author:     Michael Andres <ma@suse.de>
   Maintainer: Michael Andres <ma@suse.de>

/-*/
#ifndef NCtext_h
#define NCtext_h

#include <iosfwd>

#include <list>
using namespace std;

#include "NCstring.h"
#include "NCWidget.h"
class NCursesWindow;

///////////////////////////////////////////////////////////////////
//
//	CLASS NAME : NCtext
//
//	DESCRIPTION :
//
class NCtext {

  friend std::ostream & operator<<( std::ostream & STREAM, const NCtext & OBJ );

  public:

    typedef list<NCstring>::iterator       iterator;
    typedef list<NCstring>::const_iterator const_iterator;

  private:

    static const NCstring emptyStr;

  protected:

    list<NCstring> mtext;
    bool           sawnl;

    virtual void lset( const NCstring & ntext );

  public:

    NCtext( const NCstring & nstr = "" );
    virtual ~NCtext();

    unsigned Lines()   const;
    unsigned Columns() const;

    const list<NCstring> & Text() const { return mtext; }
    const NCstring &       operator[]( unsigned idx ) const;

    const_iterator begin() const { return mtext.begin(); }
    const_iterator end()   const { return mtext.end(); }
};

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//
//	CLASS NAME : NClabel
//
//	DESCRIPTION :
//
class NClabel : protected NCtext {

  friend std::ostream & operator<<( std::ostream & STREAM, const NClabel & OBJ );

  protected:

    unsigned hotline;

    void stripHotkey();

    virtual void lset( const NCstring & ntext ) {
      NCtext::lset( ntext );
      stripHotkey();
    }

  public:

    NClabel( const NCstring & nstr = "" )
      : NCtext( nstr )
    { stripHotkey(); }

    virtual ~NClabel() {}

  public:

    unsigned width()  const { return Columns(); }
    unsigned height() const { return Lines(); }
    wsze     size()   const { return wsze( Lines(), Columns() ); }

    void drawAt( NCursesWindow & w, chtype style, chtype hotstyle,
		 const wrect & dim,
		 const NC::ADJUST adjust = NC::TOPLEFT,
		 bool fillup = true ) const;

    //
    void drawAt( NCursesWindow & w, chtype style, chtype hotstyle,
		 const NC::ADJUST adjust = NC::TOPLEFT,
		 bool fillup = true ) const {
      drawAt( w, style, hotstyle, wrect( 0, -1 ), adjust, fillup );
    }

    void drawAt( NCursesWindow & w, chtype style, chtype hotstyle,
		 const wpos & pos,
		 const NC::ADJUST adjust = NC::TOPLEFT,
		 bool fillup = true ) const {
      drawAt( w, style, hotstyle, wrect( pos, -1 ), adjust, fillup );
    }

    void drawAt( NCursesWindow & w, chtype style, chtype hotstyle,
		 const wpos & pos, const wsze & sze,
		 const NC::ADJUST adjust = NC::TOPLEFT,
		 bool fillup = true ) const {
      drawAt( w, style, hotstyle, wrect( pos, sze ), adjust, fillup );
    }

    //
    void drawAt( NCursesWindow & w, const NCstyle::StItem & istyle,
		 const NC::ADJUST adjust = NC::TOPLEFT,
		 bool fillup = true ) const {
      drawAt( w, istyle.label, istyle.hint, wrect( 0, -1 ), adjust, fillup );
    }

    void drawAt( NCursesWindow & w, const NCstyle::StItem & istyle,
		 const wpos & pos,
		 const NC::ADJUST adjust = NC::TOPLEFT,
		 bool fillup = true ) const {
      drawAt( w, istyle.label, istyle.hint, wrect( pos, -1 ), adjust, fillup );
    }

    void drawAt( NCursesWindow & w, const NCstyle::StItem & istyle,
		 const wpos & pos, const wsze & sze,
		 const NC::ADJUST adjust = NC::TOPLEFT,
		 bool fillup = true ) const {
      drawAt( w, istyle.label, istyle.hint, wrect( pos, sze ), adjust, fillup );
    }

    void drawAt( NCursesWindow & w, const NCstyle::StItem & istyle,
		 const wrect & dim,
		 const NC::ADJUST adjust = NC::TOPLEFT,
		 bool fillup = true ) const {
      drawAt( w, istyle.label, istyle.hint, dim, adjust, fillup );
    }

    //


    bool          hasHotkey() const { return hotline != string::npos; }
    unsigned char hotkey() const { return hasHotkey() ? operator[]( hotline ).hotkey() : '\0'; }
    unsigned      hotpos() const { return hasHotkey() ? operator[]( hotline ).hotpos() : string::npos; }
};

///////////////////////////////////////////////////////////////////

#endif // NCtext_h