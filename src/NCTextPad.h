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

   File:       NCTextPad.h

   Author:     Michael Andres <ma@suse.de>
   Maintainer: Michael Andres <ma@suse.de>

/-*/
#ifndef NCTextPad_h
#define NCTextPad_h

#include <iosfwd>

#include <list>
using namespace std;

#include "NCPad.h"
#include "NCtext.h"


///////////////////////////////////////////////////////////////////
//
//	CLASS NAME : NCTextPad
//
//	DESCRIPTION :
//
class NCTextPad : public NCPad {

  friend std::ostream & operator<<( std::ostream & STREAM, const NCTextPad & OBJ );

  NCTextPad & operator=( const NCTextPad & );
  NCTextPad            ( const NCTextPad & );

  private:

    list<unsigned>           lines;
    list<unsigned>::iterator cline;

    wpos curs;
    bool curson;

    void cursor( bool on );
    void cursorOn()  { cursor( true ); }
    void cursorOff() { cursor( false ); }

    bool insert( int key );
    bool delch( bool previous = false );
    bool openLine();

    void assertSze( wsze minsze );
    void assertWidht ( unsigned minw );
    void assertHeight( unsigned minh );

  protected:

    virtual int setpos( const wpos & newpos );

  public:

    NCTextPad( int lines, int cols, const NCWidget & p );
    virtual ~NCTextPad();

  public:

    virtual void resize( wsze nsze );
    virtual int setpos();
    virtual wpos CurPos() const;
    virtual bool handleInput( int key );

    void setText( const NCtext & ntext );
    string getText() const;
};

///////////////////////////////////////////////////////////////////

#endif // NCTextPad_h