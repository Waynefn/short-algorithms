# Number2English

## Input:
+ str: decimal number
+ Number should be smaller than 1000 trillion ('1000000000000000000000').
+ Support decimal number, such as '11.05', '0.001570'.
+ Number like '561.' or '.314' is not supported.

## Output:
+ str: English form
+ Str will be capitalized.
+ Compared with normal English, the output does not contain 'and', '-' or ','.

## Return value:
+ 0: success
+ 1: error (non-number error 'abc123', decimal point error '.564')

## Example
'21315' => 'Twenty one thousand three hundred fifteen'

'98761234' => 'Ninety eight million seven hundred sixty one thousand two hundred thirty four'

'0.1564541' => 'Zero point one five six four five four one'

'12345678910111213.141592653589793' => 'Twenty three trillion six hundred seventy eight billion nine hundred ten million one hundred eleven thousand two hundred thirteen point one four one five nine two six five three five eight nine seven nine three'

'abcd' => ''  (exit(1))
