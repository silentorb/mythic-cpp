divisor = 1;

var set_divisor = function(input)
{
    divisor = input; // store the value
    return "";   // return empty string
};
set_divisor.filterName = "set_divisor";
Library.addFilter("set_divisor");

var divide = function(input)
{
    return String(input / divisor);
};
MakeRelX.filterName = "divide";
Library.addFilter("divide");