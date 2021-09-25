#pragma once

#define MIN(aLeftValue, aRightValue) (((aLeftValue)<(aRightValue))?(aLeftValue):(aRightValue))
#define MAX(aLeftValue, aRightValue) (((aLeftValue)>(aRightValue))?(aLeftValue):(aRightValue))
#define CLAMP(aValue, aMinValue, aMaxValue) ((aValue)< MIN(aMinValue, aMaxValue))?(MIN((aMinValue), (aMaxValue))):((aValue)> MAX((aMinValue), (aMaxValue)))?(MAX((aMinValue), (aMaxValue))):((aValue))
#define LERP(a, b, t) a + (b - a) * (MIN(MAX(t, 0), 1.f))
#define PI 3.14159265359