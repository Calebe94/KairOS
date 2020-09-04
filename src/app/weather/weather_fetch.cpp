/****************************************************************************
 *   July 23 00:23:05 2020
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
#include "config.h"
#include "HTTPClient.h"

#include "weather.h"
#include "weather_fetch.h"
#include "weather_forecast.h"

#include "hardware/powermgm.h"
#include "hardware/json_psram_allocator.h"

/* Utility function to convert numbers to directions */
static void weather_wind_to_string( weather_forcast_t* container, int speed, int directionDegree);

int weather_fetch_today( weather_config_t *weather_config, weather_forcast_t *weather_today ) {
    char url[512]="";
    int httpcode = -1;
    const char* weather_units_symbol = weather_config->imperial ? "F" : "C";
    const char* weather_units_char = weather_config->imperial ? "imperial" : "metric";
    
    snprintf( url, sizeof( url ), "http://%s/data/2.5/weather?lat=%s&lon=%s&appid=%s&units=%s", OWM_HOST, weather_config->lat, weather_config->lon, weather_config->apikey, weather_units_char);

    HTTPClient today_client;

    today_client.useHTTP10( true );
    today_client.begin( url );
    httpcode = today_client.GET();

    if ( httpcode != 200 ) {
        log_e("HTTPClient error %d", httpcode, url );
        today_client.end();
        return( -1 );
    }

    SpiRamJsonDocument doc( today_client.getSize() * 2 );

    DeserializationError error = deserializeJson( doc, today_client.getStream() );
    if (error) {
        log_e("weather today deserializeJson() failed: %s", error.c_str() );
        doc.clear();
        today_client.end();
        return( -1 );
    }

    today_client.end();

    weather_today->valide = true;
    snprintf( weather_today->temp, sizeof( weather_today->temp ), "%0.1f°%s", doc["main"]["temp"].as<float>(), weather_units_symbol);
    snprintf( weather_today->humidity, sizeof( weather_today->humidity ),"%f%%", doc["main"]["humidity"].as<float>() );
    snprintf( weather_today->pressure, sizeof( weather_today->pressure ),"%fpha", doc["main"]["pressure"].as<float>() );
    strcpy( weather_today->icon, doc["weather"][0]["icon"] );
    strcpy( weather_today->name, doc["name"] );

    int directionDegree = doc["wind"]["deg"].as<int>();
    int speed = doc["wind"]["speed"].as<int>();
    weather_wind_to_string( weather_today, speed, directionDegree );

    doc.clear();
    return( httpcode );
}

int weather_fetch_forecast( weather_config_t *weather_config, weather_forcast_t * weather_forecast ) {
    char url[512]="";
    int httpcode = -1;
    const char* weather_units_symbol = weather_config->imperial ? "F" : "C";
    const char* weather_units_char = weather_config->imperial ? "imperial" : "metric";

    snprintf( url, sizeof( url ), "http://%s/data/2.5/forecast?cnt=%d&lat=%s&lon=%s&appid=%s&units=%s", OWM_HOST, WEATHER_MAX_FORECAST, weather_config->lat, weather_config->lon, weather_config->apikey, weather_units_char);

    HTTPClient forecast_client;

    forecast_client.useHTTP10( true );
    forecast_client.begin( url );
    httpcode = forecast_client.GET();

    if ( httpcode != 200 ) {
        log_e("HTTPClient error %d", httpcode, url );
        forecast_client.end();
        return( -1 );
    }

    SpiRamJsonDocument doc( forecast_client.getSize() * 2 );

    DeserializationError error = deserializeJson( doc, forecast_client.getStream() );
    if (error) {
        log_e("weather forecast deserializeJson() failed: %s", error.c_str() );
        doc.clear();
        forecast_client.end();
        return( -1 );
    }

    forecast_client.end();

    weather_forecast[0].valide = true;
    for ( int i = 0 ; i < WEATHER_MAX_FORECAST ; i++ ) {
        weather_forecast[ i ].timestamp = doc["list"][i]["dt"].as<long>() | 0;
        snprintf( weather_forecast[ i ].temp, sizeof( weather_forecast[ i ].temp ),"%0.1f°%s", doc["list"][i]["main"]["temp"].as<float>(), weather_units_symbol );
        snprintf( weather_forecast[ i ].humidity, sizeof( weather_forecast[ i ].humidity ),"%f%%", doc["list"][i]["main"]["humidity"].as<float>() );
        snprintf( weather_forecast[ i ].pressure, sizeof( weather_forecast[ i ].pressure ),"%fpha", doc["list"][i]["main"]["pressure"].as<float>() );
        strlcpy( weather_forecast[ i ].icon, doc["list"][i]["weather"][0]["icon"] | "n/a", sizeof(  weather_forecast[ i ].icon ) );
        strlcpy( weather_forecast[ i ].name, doc["city"]["name"] | "n/a", sizeof( weather_forecast[ i ].name ) );

        int directionDegree = doc["list"][i]["wind"]["deg"].as<int>() | 0;
        int speed = doc["list"][i]["wind"]["speed"].as<int>() | 0;
        weather_wind_to_string( &weather_forecast[i], speed, directionDegree );
    }

    doc.clear();
    return( httpcode );
}

void weather_wind_to_string( weather_forcast_t* container, int speed, int directionDegree )
{
    const char *dir = "N";
    if ( directionDegree > 348 )
        ; // already set to "N"
    else if ( directionDegree > 326 )
        dir = "NNW";
    else if ( directionDegree > 303 )
        dir = "NW";
    else if ( directionDegree > 281 )
        dir = "WNW";
    else if ( directionDegree > 258 )
        dir = "W";
    else if ( directionDegree > 236 )
        dir = "WSW";
    else if ( directionDegree > 213 )
        dir = "SW";
    else if ( directionDegree > 191 )
        dir = "SSW";
    else if ( directionDegree > 168 )
        dir = "S";
    else if ( directionDegree > 146 )
        dir = "SSE";
    else if ( directionDegree > 123 )
        dir = "SE";
    else if ( directionDegree > 101 )
        dir = "ESE";
    else if ( directionDegree > 78 )
        dir = "E";
    else if ( directionDegree > 56 )
        dir = "ENE";
    else if ( directionDegree > 33 )
        dir = "NE";
    else if ( directionDegree > 11 )
        dir = "NNE";
    snprintf( container->wind, sizeof(container->wind), "%d %s", speed, dir);
    return;
}