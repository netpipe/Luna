from math import cos,sin,acos,asin,tan
from math import degrees,radians
from datetime import date,datetime,time,timedelta

def sunrise_sunset(latitude,longitude,d,t=0.5,timezone=0):
    dateOrdinal = d.toordinal()-734124+40529
    
    # Julian Day and Century calculations
    julianDay         = dateOrdinal+2415018.5+t-timezone/24
    julianCentury     = (julianDay-2451545)/36525

    # Detailed calculation
    # Inspired by: http://www.esrl.noaa.gov/gmd/grad/solcalc/calcdetails.html
    geomMeanLongSun   = 280.46646+julianCentury*(36000.76983+julianCentury*0.0003032)%360
    geomMeanAnomSun   = 357.52911+julianCentury*(35999.05029-0.0001537*julianCentury)
    eccentEarthOrbit  = 0.016708634-julianCentury*(0.000042037+0.0000001267*julianCentury)
    sunEqOfCtr        = sin(radians(geomMeanAnomSun))*(1.914602-julianCentury*(0.004817+0.000014*julianCentury))+sin(radians(2*geomMeanAnomSun))*(0.019993-0.000101*julianCentury)+sin(radians(3*geomMeanAnomSun))*0.000289
    sunTrueLong       = geomMeanLongSun+sunEqOfCtr
    sunAppLong        = sunTrueLong-0.00569-0.00478*sin(radians(125.04-1934.136*julianCentury))
    meanObliqEcliptic = 23+(26+((21.448-julianCentury*(46.815+julianCentury*(0.00059-julianCentury*0.001813))))/60)/60
    obliqCorr         = meanObliqEcliptic+0.00256*cos(radians(125.04-1934.136*julianCentury))
    sunDeclination    = degrees(asin(sin(radians(obliqCorr))*sin(radians(sunAppLong))))
    varY              = tan(radians(obliqCorr/2))*tan(radians(obliqCorr/2))
    eqOfTime          = 4*degrees(varY*sin(2*radians(geomMeanLongSun))-2*eccentEarthOrbit*sin(radians(geomMeanAnomSun))+4*eccentEarthOrbit*varY*sin(radians(geomMeanAnomSun))*cos(2*radians(geomMeanLongSun))-0.5*varY*varY*sin(4*radians(geomMeanLongSun))-1.25*eccentEarthOrbit*eccentEarthOrbit*sin(2*radians(geomMeanAnomSun)))
    hourAngleSunrise  = degrees(acos(cos(radians(90.833))/(cos(radians(latitude))*cos(radians(sunDeclination)))-tan(radians(latitude))*tan(radians(sunDeclination))))

    #sunset and sunrise final calculations
    solarNoon         = (720-4*longitude-eqOfTime+timezone*60)/1440
    sunriseTime       = (solarNoon-hourAngleSunrise*4/1440) #edge case under/over 0/1
    sunsetTime        = (solarNoon+hourAngleSunrise*4/1440) #edge case under/over 0/1
    
    #solar azimuth calculations (solar azimuth is degrees CW from North)
    trueSolarTime = ((t*1440)+eqOfTime+(4*longitude)-(60*timezone)) % 1440
    if trueSolarTime/4 < 0: hourAngle = trueSolarTime/4+180 
    else: hourAngle = trueSolarTime/4-180
    solarZenithAngle = degrees(acos(sin(radians(latitude))*sin(radians(sunDeclination))+cos(radians(latitude))*cos(radians(sunDeclination))*cos(radians(hourAngle))))
    if hourAngle > 0: solarAzimuthAngle = (degrees(acos(((sin(radians(latitude))*cos(radians(solarZenithAngle)))-sin(radians(sunDeclination)))/(cos(radians(latitude))*sin(radians(solarZenithAngle)))))+180) % 360 
    else: solarAzimuthAngle = (540 -        degrees(acos(((sin(radians(latitude))*cos(radians(solarZenithAngle)))-sin(radians(sunDeclination)))/(cos(radians(latitude))*sin(radians(solarZenithAngle)))))) % 360
    
    # Solar azimuth calculation (at sunrise)
    solarZenithAngleSunrise  = degrees(acos(sin(radians(latitude))*sin(radians(sunDeclination))+cos(radians(latitude))*cos(radians(sunDeclination))*cos(radians(hourAngleSunrise))))
    # Solar Zenith Angle is approximately the same at sunrise and sunset, so use it for both azimuth calculations
    solarAzimuthAngleSunrise = (540 - degrees(acos(((sin(radians(latitude))*cos(radians(solarZenithAngleSunrise)))-sin(radians(sunDeclination)))/(cos(radians(latitude))*sin(radians(solarZenithAngleSunrise)))))) % 360
    solarAzimuthAngleSunset  = (degrees(acos(((sin(radians(latitude))*cos(radians(solarZenithAngleSunrise)))-sin(radians(sunDeclination)))/(cos(radians(latitude))*sin(radians(solarZenithAngleSunrise)))))+180) % 360 

    
    # Sunrise and sunset may be on different UTC days
    sunriseDate = d
    sunsetDate = d
    
    # If not using timezones, there is the possibility for returning < 0:00, > 24:00
    if sunriseTime < 0:
        sunriseDate -= timedelta(days = 1)
    elif sunriseTime > 1: 
        sunriseDate += timedelta(days = 1)
    sunriseTime = sunriseTime % 1
    
    if sunsetTime < 0:
        sunsetDate -= timedelta(days = 1)
    elif sunsetTime > 1:
        sunsetDate += timedelta(days = 1)
    sunsetTime = sunsetTime % 1
    
    # Sunset time calculation
    sunsetHour = int(24.0*sunsetTime)
    sunsetMinute = int((24.0*sunsetTime-sunsetHour)*60)
    sunsetSecond = int(((24.0*sunsetTime-sunsetHour)*60-sunsetMinute)*60)
    sunsetHMS = time(sunsetHour, sunsetMinute, sunsetSecond)
    #sunset = str(sunsetHour).zfill(2)+":"+str(sunsetMinute).zfill(2)+":"+str(sunsetSecond).zfill(2)

    # Sunrise time calculation
    sunriseHour = int(24.0*sunriseTime)
    sunriseMinute = int((24.0*sunriseTime-sunriseHour)*60)
    sunriseSecond = int(((24.0*sunriseTime-sunriseHour)*60-sunriseMinute)*60)
    sunriseHMS = time(sunriseHour, sunriseMinute, sunriseSecond)
    #sunrise = str(sunriseHour).zfill(2)+":"+str(sunriseMinute).zfill(2)+":"+str(sunriseSecond).zfill(2)

    # Combine time and date into a datetime object
    sunset = datetime.combine(sunsetDate, sunsetHMS)
    sunrise = datetime.combine(sunriseDate, sunriseHMS)
    
    # Formatting output
    #sunset = str(sunsetHour).zfill(2)+":"+str(sunsetMinute).zfill(2)+":"+str(sunsetSecond).zfill(2)
    #sunrise = str(sunriseHour).zfill(2)+":"+str(sunriseMinute).zfill(2)+":"+str(sunriseSecond).zfill(2)

    #return output dictionary
    return {"sunrise":{"datetime":sunrise, "solarazimuth":solarAzimuthAngleSunrise}, "sunset":{"datetime":sunset, "solarazimuth":solarAzimuthAngleSunset}}

def time_until_next_sunrise_sunset(latitude,longitude,datetimeutc):
    sunrise = sunset = sunrise_sunset(latitude, longitude, datetimeutc.date())
    sunriseDifference = sunrise["sunrise"]["datetime"] - datetimeutc
    sunsetDifference = sunset["sunset"]["datetime"] - datetimeutc
    
    utcSunriseDate = utcSunsetDate = datetimeutc.date()
    while sunriseDifference.days != 0:
        if sunrise["sunrise"]["datetime"] < datetimeutc:
            utcSunriseDate += timedelta(days = 1)
        elif sunrise["sunrise"]["datetime"] > datetimeutc:
            utcSunriseDate -= timedelta(days = 1)
        sunrise = sunrise_sunset(latitude, longitude, utcSunriseDate)
        sunriseDifference = sunrise["sunrise"]["datetime"] - datetimeutc

    while sunsetDifference.days != 0:
        if sunset["sunset"]["datetime"] < datetimeutc:
            utcSunsetDate += timedelta(days = 1)
        elif sunset["sunset"]["datetime"] > datetimeutc:
            utcSunsetDate -= timedelta(days = 1)
        sunset = sunrise_sunset(latitude, longitude, utcSunsetDate)
        sunsetDifference = sunset["sunset"]["datetime"] - datetimeutc
  
    return {"nextSunrise":sunriseDifference, "nextSunset":sunsetDifference}

def time_of_next_sunrise_sunset(latitude,longitude,datetimeutc):
    sunrise = sunset = sunrise_sunset(latitude, longitude, datetimeutc.date())
    sunriseDifference = sunrise["sunrise"]["datetime"] - datetimeutc
    sunsetDifference = sunset["sunset"]["datetime"] - datetimeutc
    
    utcSunriseDate = utcSunsetDate = datetimeutc.date()
    while sunriseDifference.days != 0:
        if sunrise["sunrise"]["datetime"] < datetimeutc:
            utcSunriseDate += timedelta(days = 1)
        elif sunrise["sunrise"]["datetime"] > datetimeutc:
            utcSunriseDate -= timedelta(days = 1)
        sunrise = sunrise_sunset(latitude, longitude, utcSunriseDate)
        sunriseDifference = sunrise["sunrise"]["datetime"] - datetimeutc

    while sunsetDifference.days != 0:
        if sunset["sunset"]["datetime"] < datetimeutc:
            utcSunsetDate += timedelta(days = 1)
        elif sunset["sunset"]["datetime"] > datetimeutc:
            utcSunsetDate -= timedelta(days = 1)
        sunset = sunrise_sunset(latitude, longitude, utcSunsetDate)
        sunsetDifference = sunset["sunset"]["datetime"] - datetimeutc
  
    return {"nextSunrise":sunrise["sunrise"], "nextSunset":sunset["sunset"]}

def rounded_hours_until_next_sunrise_sunset(latitude, longitude, datetimeutc):
    timeUntil = time_until_next_sunrise_sunset(latitude, longitude, datetimeutc)
    sunriseHours = round(timeUntil["nextSunrise"].seconds / 3600)    
    sunsetHours = round(timeUntil["nextSunset"].seconds / 3600)
    
    return {"roundedHoursNextSunrise":str(sunriseHours).zfill(2), "roundedHoursNextSunset":str(sunsetHours).zfill(2)}



