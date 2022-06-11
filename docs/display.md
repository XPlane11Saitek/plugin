
# DISPLAY

* `INT`
* `FLOAT`
* `SHORT`
* `DOUBLE`
* `SMART`
* `INT1`
* `INT2`
* `MINT`
* `<DISPLAY>/<N>`

# DOUBLE
Description: Print a number with three decimal places.
Format: NNNN.N
Limited: -9.999:99.999
Example:
1. 125.50  = [25.500]
2. 125.505 = [25.505]
3. -1 = [-1.000]

# FLOAT
Description: Print a number with two decimal places.
Format: NNN.NN
Limited: -99.99:999.99
Example:
1. 125.50  = [125.50]
2. 125.505 = [125.50.]
3. -10 = [-10.00]

# SHORT
Description: Print a number with one decimal places.
Format: NNNN.N
Limited: -999.9:9999.9
Example:
1. 125.50  = [_125.5]
2. 125.505 = [_125.5]
3. -10 = [_-10.0]

# INT
Description: Display integer number
Format: NNNNN
Limited: -9999:99999
Example:
1. 35000 = [35000]
2. 180 = [__180]
3. -10 = [__-10]

# SMART
Description: Print a number with three decimal places or less
Format: NN.NNN | NNN.NN | NNNN.N | NNNNN.
Limited: 0:Infinity
Example:
1. 125.50  = [_125.5]
2. 125.505 = [25.505]
3. -10 = [__-10]

# INT1
Description: Display number 1 and integer number
Format: 1_NNN
Limited: 0:999
Example:
1. 180 = [1_180]

# INT2
Description: Display number 2 and integer number
Format: 2_NNN
Limited: 0:999
Example:
1. 180 = [2_180]

# MINT
Description: Display minus and integer number
Format: -NNN-
Limited: 0:999
Example:
1. 180 = [-180-]
2. 270 = [-270-]

# DIV
Description: This is only change point
Example
1. INT/100 ; 180 = [____1]
2. INT/10 ;  180 = [___18]
3. FOLAT/100 ; 180 = [__1.80]
