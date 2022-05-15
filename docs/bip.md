

## Configure Saitek Pro Flight Backlit Information Panel
```
BIP <ID> <ROW>:<COLUM> <COLOR> <RANGE>
BIP <ID> <ROW>:<COLUM> NAME <NAME>
```
* `ID` -  Number panel 
* `ROW` - Number row
* `COLUM` - Number cell in row
* `COLOR` - Activated collor 
* `RANGE` - dataref(value)
* `NAME` - Name device on virtual panel (0.4.0)

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
Or flash collor in 1 second ( Added in 0.4.0 as testing)
* `GREEN-OFF`
* `YELLOW-OFF`
* `RED-OFF`

### RANGE
Range mast be next format
```
dataref(<dataref>){<VALUE-FROM>:<VALUE-TO>}
array(<dataref>[<infex>]){<VALUE-FROM>:<VALUE-TO>}
```
Always remember. The indication will work if the value is in this value range.

Supported 
* dataref - Information given from XPlane 11 Values
* array - Information given from XPlane 11 Array values with pos index

You can find the list variables at the following link.
https://developer.x-plane.com/datarefs/

WARNING.
You should always keep track of the types of variables.
* If type float - you mast use dataref
* If type int - you mast use dataref
* If type float[8] - you mast use array
* If type int[50] - you mast use array.

```
(<RANGE>) OR (<RANGE>)
```
```
(<RANGE>) AND (<RANGE>)
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

