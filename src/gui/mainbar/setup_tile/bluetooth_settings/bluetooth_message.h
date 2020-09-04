/****************************************************************************
 *   Aug 18 12:37:31 2020
 *   Copyright  2020  Dirk Brosswick
 *   Email: dirk.brosswick@googlemail.com
 ****************************************************************************/
 
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef _BLUETOOTH_MESSAGE_H
    #define _BLUETOOTH_MESSAGE_H

    #include <TTGO.h>

    struct src_icon_t {
        const char src_name[ 24 ];
        const int32_t vibe;
        const lv_img_dsc_t *img;
    };

    void bluetooth_message_tile_setup( void );
    void bluetooth_message_disable( void );
    void bluetooth_message_enable( void );

#endif // _BLUETOOTH_MESSAGE_H