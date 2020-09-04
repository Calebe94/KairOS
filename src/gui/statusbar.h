/****************************************************************************
 *   Tu May 22 21:23:51 2020
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
#ifndef _STATUSBAR_H

    #define _STATUSBAR_H

    #include "config.h"

    #define STATUSBAR_HEIGHT            26
    #define STATUSBAR_EXPAND_HEIGHT     160

    typedef struct {
        lv_obj_t *icon;
        const void *symbol;
        lv_align_t align;
        lv_style_t *style;
    } lv_status_bar_t;

    typedef enum {
        STATUSBAR_BATTERY_PERCENT,
        STATUSBAR_BATTERY,
        STATUSBAR_BLUETOOTH,
        STATUSBAR_WIFI,
        STATUSBAR_BELL,
        STATUSBAR_WARNING,
        STATUSBAR_ALARM,
        STATUSBAR_NUM
    } statusbar_icon_t;
    
    typedef enum {
        STATUSBAR_STYLE_NORMAL,
        STATUSBAR_STYLE_WHITE,
        STATUSBAR_STYLE_RED,
        STATUSBAR_STYLE_GRAY,
        STATUSBAR_STYLE_YELLOW,
        STATUSBAR_STYLE_GREEN,
        STATUSBAR_STYLE_BLUE,
        STATUSBAR_STYLE_NUM
    } statusbar_style_t;

    /*
     * @brief setup statusbar
     */
    void statusbar_setup( void );
    /*
     * @brief hide an icon from statusbar
     * 
     * @param icon  icon name
     */
    void statusbar_hide_icon( statusbar_icon_t icon );
    /*
     * @brief show an icon from statusbar
     * 
     * @param icon  icon name
     */
    void statusbar_show_icon( statusbar_icon_t icon );
    /*
     * @brief hide an icon from statusbar
     * 
     * @param icon  icon name
     * @param style style name
     */
    void statusbar_style_icon( statusbar_icon_t icon, statusbar_style_t style );
    /*
     * @brief refresh/redraw statusbar
     */
    void statusbar_refresh( void );
    /*
     * @brief update stepcounter from statusbar
     * 
     * @param   step    stepcounter value
     */
    void statusbar_update_stepcounter( int step );
    /*
     * @brief update battery icon and ther state
     * 
     * @param   percent     displayed value in percent
     * @param   charging    true or false, true means charging
     * @param   plug        true or false, true means pluged
     */
    void statusbar_update_battery( int32_t percent, bool charging, bool plug );
    /*
     * @brief   set wifistate and label
     * 
     * @param   state       true or false, true means active
     * @param   wifiname    label to displayed text like "scan","connecting" and so on
     */
    void statusbar_wifi_set_state( bool state, const char *wifiname );
    void statusbar_wifi_set_ip_state( bool state, const char *ip );
    void statusbar_bluetooth_set_state( bool state );
    /*
     * @brief hide the statusbar
     * 
     * @param   hide    true or false, ture means statusbar is hide
     */
    void statusbar_hide( bool hide );

#endif // _STATUSBAR_H

