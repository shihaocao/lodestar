#include "GPSMonitor.hpp"

GPSMonitor::GPSMonitor(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "imu_monitor", offset),
    GPS(&GPSSerial),
    functional_f("gps.functional"),
    has_fix_f("gps.fix"),
    has_new_nmea_f("gps.new"),
    lat_long_f("gps.lat_long")
    {
        //add statefields to registry
        add_internal_field(has_fix_f);
        add_internal_field(has_new_nmea_f);
        add_internal_field(lat_long_f);

        // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
        GPS.begin(9600);
        // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data)
        // including altitude
        GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
        // uncomment this line to turn on only the "minimum recommended" data
        // GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
        // For parsing data, we don't suggest using anything but either RMC only or
        // RMC+GGA since the parser doesn't care about other sentences at this time
        // Set the update rate (uncomment the one you want.)
        // GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
        // GPS.sendCommand(PMTK_SET_NMEA_UPDATE_200_MILLIHERTZ); // 5 second update
        // time

        // command to set actual 5HZ fix updating
        GPS.sendCommand(PMTK_API_SET_FIX_CTL_5HZ);

        GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ); // 5 hz set by shihao
        // For the parsing code to work nicely and have time to sort thru the data,
        // and print it out we don't suggest using anything higher than 1 Hz

        // Request updates on antenna status, comment out to keep quiet
        GPS.sendCommand(PGCMD_ANTENNA);

        functional_f.set(false);
        has_fix_f.set(false);    
        has_new_nmea_f.set(false);
        lat_long_f.set(lin::Vector2f{0});
    }

void GPSMonitor::update_state_fields(){

    lat_long_f.set({
        GPS.latitudeDegrees,
        GPS.longitudeDegrees
    });

}

void GPSMonitor::execute(){

    // char c = GPS.read();
    GPS.read(); // pretty sure this is necessary

    if (GPS.newNMEAreceived()) {
        // a tricky thing here is if we print the NMEA sentence, or data
        // we end up not listening and catching other sentences!
        // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
        // Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived()
        // flag to false

        //if this line is reached, there is new data, so set flag to true
        has_new_nmea_f.set(true);
        if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag
                                        // to false

            // however, if we fail to parse for whatever reason, don't trust data
            has_new_nmea_f.set(false);
    }
    else has_new_nmea_f.set(false);

    // only update the statefields if we have new and correctly parsed data
    if(has_new_nmea_f.get()){
        update_state_fields();
    }
}