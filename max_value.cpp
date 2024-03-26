#include "max_value.h"
#include <algorithm>

using namespace std;

double calculateMaxValue(double* nums, int n)
{
	double minV = nums[0], maxV = nums[0];
	for (int i = 1; i < n; ++i)
	{
		if (nums[i] > 0)
		{
			maxV = max({ maxV + nums[i], maxV * nums[i], maxV / nums[i] });
			minV = min({ minV - nums[i], minV * nums[i], minV / nums[i] });
		}
		else if (nums[i] < 0)
		{
			double maxV_ = maxV;
			maxV = max({ maxV - nums[i], minV * nums[i], minV / nums[i] });
			minV = min({ minV + nums[i], maxV_ * nums[i], maxV_ / nums[i] });
		}
		else
		{
			minV = min(0., minV);
			maxV = max(0., maxV);
		}
	}

	return maxV;

}
