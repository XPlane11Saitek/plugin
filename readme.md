# Demonstration
Demonstration youtube
https://www.youtube.com/watch?v=P-q9Ev7aooU

# Plugin for Saitek device for XPlane 11

## Support 
* Logitech Saitek Pro Flight Multi Panel
* Logitech G Saitek Pro Flight Radio Panel
* Logitech G Saitek Pro Flight Switch Panel
* Saitek Pro Flight Backlit Information Panel

## Configure have per configuration
* Cessna 172SP
* Beechcraft Baron 58
* Cirrus Vision SF50
* Zibo Boeing 737-800 (Experemental and testing) (>=4.4.0)
* Default pre configuration for any plane.

## Information 
This plugin is driver for device. 
You can configue as you with from configure file.

## Requirements
* XPLane 11 with version 1.50 or high (SDK3)
* Windows(version 10 and high)

# Install 
This is global plugin only. Setup need only 
```
<XPLANLE 11 DIRECOTY>/Resources/plugins/
```

## Install requirements
Pluging need setup:as file
```
<XPLANLE 11 DIRECOTY>/Resources/plugins/saitek/64/win.xpl
```
Plugin reading configure form file
```
<XPLANLE 11 DIRECOTY>/Resources/plugins/saitek/config/<ICAO-CODE-PLANE>.txt
```

# Confuguration 
## Split file
Not recomendation work with one file. This file is very big. And bed for reading.
Recomendation group by diff files.
```
LOAD FROM FILE <filename>
```
Filename mast be without ```.txt```

# This driver support multiple count devices.

## Configure Saitek Pro Flight Backlit Information Panel
```
BIP <ID> <ROW><COLUM> <COLOR> <VALUE>
```
* `ID` -  Number panel 
* `ROW` - Number row
* `COLUM` - Number cell in row
* `COLOR` - Activated collor 
* `VALUE` - dataref(value

### ID 
* ```-1``` - This configuration for all panel
* ```0``` - First panel as found.
* ```1``` - Second panel as found.
Order panel by usb address based on nuber usb port.

### ROW
- ```-1```  - This configuration for all row
- ```0``` - First row
- ```1``` - Central row
- ```2``` - Lower row

### COLUM 
- ```-1``` - This configuration for all collum
- ```0```-```7``` - Number cell. Number starting from 0.

### COLOR
One of
* `OFF`
* `GREEN`
* `YELLOW`
* `RED`

### VALUE
Value mast be next format
```
dataref(<dataref>){<VALUE-FROM>:<VALUE-TO>}
```
```
array(<dataref>[<infex>]){<VALUE-FROM>:<VALUE-TO>}
```
```
(<VALUE>) OR (<VALUE>)
```
```
(<VALUE>) AND (<VALUE>)
```

### Example
```
BIP -1 -1:-1 OFF (array(sim/cockpit/electrical/battery_array_on[0]){0:0}) AND ((array(sim/cockpit2/electrical/generator_amps[0]){0:1}) AND (array(sim/cockpit2/electrical/generator_amps[1]){0:1}))
BIP 1 2:0 YELLOW array(sim/flightmodel2/wing/flap1_deg[0]){1:9}
BIP 1 2:0 GREEN array(sim/flightmodel2/wing/flap1_deg[0]){9:11}
BIP 1 2:0 YELLOW array(sim/flightmodel2/wing/flap1_deg[0]){11:19}
BIP 1 2:0 GREEN array(sim/flightmodel2/wing/flap1_deg[0]){19:21}
BIP 1 2:0 YELLOW array(sim/flightmodel2/wing/flap1_deg[0]){21:29}

```
Driver support multiple line in one cell.
Example for flap Cessna 172
```
BIP 1 2:0 YELLOW array(sim/flightmodel2/wing/flap1_deg[0]){1:9}
BIP 1 2:0 GREEN array(sim/flightmodel2/wing/flap1_deg[0]){9:11}
BIP 1 2:0 YELLOW array(sim/flightmodel2/wing/flap1_deg[0]){11:19}
BIP 1 2:0 GREEN array(sim/flightmodel2/wing/flap1_deg[0]){19:21}
BIP 1 2:0 YELLOW array(sim/flightmodel2/wing/flap1_deg[0]){21:29}
```

## Configure Logitech G Saitek Pro Flight Switch Panel
```
# FOR LED
SWITCH <ID> [LEFT|CENTER|RIGHT] <COLOR> <VALUE>
# FOR ACTION
SWITCH <ID> <BUTTON> <MODE> <ACTION>
```
* `COLOR`/`VALUE` read docs for configure ```Saitek Pro Flight Backlit Information Panel```
* `BUTTON` - Name for button
* `MODE` - Type action for mode
* `ACTION` - Action for type

### ID
* ```-1``` - This configuration for all panel
* ```0``` - First panel as found.
* ```1``` - Second panel as found.
Order panel by usb address based on nuber usb port.

### COLOR/VALUE
Read docs for configure ```Saitek Pro Flight Backlit Information Panel```

### BUTTON
Support buttons
* `MAG_OFF`
* `MAG_RIGHT`
* `MAG_LEFT`
* `MAG_BOTH`
* `ENG_START`

* `MASTER_BATTERY`
* `MASTER_ALTENATOR`

* `AVIONICS_POWER`
* `FUEL_PUMP`
* `DE_ICE`
* `PITOT_HEAT`

* `COWL_FLAPS`

* `PANEL_LIGHTS`
* `BEACON_LIGHTS`
* `NAV_LIGHTS`
* `STROBE_LIGHTS`
* `TAXI_LIGHTS`
* `LANDING_LIGHTS`

* `GEAR_SWITCH_UP`
* `GEAR_SWITCH_DOWN`


### MODE and ACTION
mode `ON` or `OFF` OR `CMD` - when executed command
* `ON` - exec only when push on button
* `OFF` - exec only when release on button
* `CMD` - exec when push and release button

action `command` `set` `push` `on` `off`

### Exmaple

For cessna 172
```
SWITCH 0 MAG_OFF ON command(sim/magnetos/magnetos_off)
SWITCH 0 MAG_RIGHT ON command(sim/magnetos/magnetos_right_1)
SWITCH 0 MAG_LEFT ON command(sim/magnetos/magnetos_left_1)
SWITCH 0 MAG_BOTH ON command(sim/magnetos/magnetos_both_1)
SWITCH 0 ENG_START CMD push(sim/ignition/ignition_up_1)

SWITCH 0 GEAR_SWITCH_UP ON set(dataref(sim/cockpit2/controls/parking_brake_ratio):=0.000000)
SWITCH 0 GEAR_SWITCH_DOWN ON set(dataref(sim/cockpit2/controls/parking_brake_ratio):=1.000000)

SWITCH 1 PANEL_LIGHTS CMD push(sim/annunciator/test_all_annunciators)

# Multiple Action for one button
SWITCH 0 PITOT_HEAT ON command(sim/ice/pitot_heat0_on)
SWITCH 0 PITOT_HEAT OFF command(sim/ice/pitot_heat0_off)
SWITCH 0 PITOT_HEAT ON command(sim/ice/pitot_heat1_on)
SWITCH 0 PITOT_HEAT OFF command(sim/ice/pitot_heat1_off)

```

## Configuration Logitech Saitek Pro Flight Multi Panel and Logitech G Saitek Pro Flight Radio Panel
Configuration radio and multi panel based on object.

```
TODO ADD Docs for mapping
```
