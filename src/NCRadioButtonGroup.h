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

   File:       NCRadioButtonGroup.h

   Author:     Michael Andres <ma@suse.de>
   Maintainer: Michael Andres <ma@suse.de>

/-*/
#ifndef NCRadioButtonGroup_h
#define NCRadioButtonGroup_h

#include <iosfwd>

#include "YRadioButtonGroup.h"
#include "NCWidget.h"

class NCRadioButtonGroup;

///////////////////////////////////////////////////////////////////
//
//	CLASS NAME : NCRadioButtonGroup
//
//	DESCRIPTION :
//
class NCRadioButtonGroup : public YRadioButtonGroup, public NCWidget {

  friend std::ostream & operator<<( std::ostream & STREAM, const NCRadioButtonGroup & OBJ );

  NCRadioButtonGroup & operator=( const NCRadioButtonGroup & );
  NCRadioButtonGroup            ( const NCRadioButtonGroup & );

  private:

  protected:

    virtual const char * location() const { return "NCRadioButtonGroup"; }

  public:

    NCRadioButtonGroup( NCWidget * parent, YWidgetOpt & opt );
    virtual ~NCRadioButtonGroup();

    virtual long nicesize( YUIDimension dim ) { return YRadioButtonGroup::nicesize( dim ); }
    virtual void setSize( long newwidth, long newheight );

    virtual void addRadioButton(YRadioButton *button);
    virtual void removeRadioButton(YRadioButton *button);

};

///////////////////////////////////////////////////////////////////

#endif // NCRadioButtonGroup_h