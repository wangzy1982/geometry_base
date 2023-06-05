#ifndef _WGEO_CORE_INTERVAL_
#define _WGEO_CORE_INTERVAL_

#include "tolerance.h"

class Interval {
public:
    double Min;
    double Max;
public:
    Interval();
    Interval(double d);
    Interval(double min, double max);
    bool IsIntersected(double d, double epsilon) const;
    bool IsIntersected(const Interval& interval, double epsilon) const;
};

inline Interval operator+(const Interval& interval0, const Interval& interval1) {
    return Interval(interval0.Min + interval1.Min, interval0.Max + interval1.Max);
}

inline Interval operator+(const Interval& interval, double d) {
    return Interval(interval.Min + d, interval.Max + d);
}

inline Interval operator+(double d, const Interval& interval) {
    return Interval(interval.Min + d, interval.Max + d);
}

inline Interval operator-(const Interval& interval0, const Interval& interval1) {
    return Interval(interval0.Min - interval1.Max, interval0.Max - interval1.Min);
}

inline Interval operator-(const Interval& interval, double d) {
    return Interval(interval.Min - d, interval.Max - d);
}

inline Interval operator-(double d, const Interval& interval) {
    return Interval(d - interval.Max, d - interval.Min);
}

inline Interval operator-(const Interval& interval) {
    return Interval(-interval.Max, -interval.Min);
}

inline Interval operator*(const Interval& interval0, const Interval& interval1) {
    double min = interval0.Min * interval1.Min;
    double max = min;
    double t = interval0.Max * interval1.Min;
    if (t < min) {
        min = t;
    } else if (t > max) {
        max = t;
    }
    t = interval0.Max * interval1.Max;
    if (t < min) {
        min = t;
    } else if (t > max) {
        max = t;
    }
    t = interval0.Min * interval1.Max;
    if (t < min) {
        min = t;
    } else if (t > max) {
        max = t;
    }
    return Interval(min, max);
}

inline Interval operator*(const Interval& interval, double d) {
    if (d >= 0) {
        return Interval(interval.Min * d, interval.Max * d);
    }
    return Interval(interval.Max * d, interval.Min * d);
}

inline Interval operator*(double d, const Interval& interval) {
    if (d >= 0) {
        return Interval(interval.Min * d, interval.Max * d);
    }
    return Interval(interval.Max * d, interval.Min * d);
}

inline Interval operator/(const Interval& interval0, const Interval& interval1) {
    if (interval1.Max < 0 || interval1.Min > 0) {
        double min = interval0.Min / interval1.Min;
        double max = min;
        double t = interval0.Max / interval1.Min;
        if (t < min) {
            min = t;
        } else if (t > max) {
            max = t;
        }
        t = interval0.Max / interval1.Max;
        if (t < min) {
            min = t;
        } else if (t > max) {
            max = t;
        }
        t = interval0.Min / interval1.Max;
        if (t < min) {
            min = t;
        } else if (t > max) {
            max = t;
        }
        return Interval(min, max);
    }
    throw "div zero error";
}

inline Interval operator/(const Interval& interval, double d) {
    if (d > 0) {
        return Interval(interval.Min / d, interval.Max / d);
    } 
    if (d < 0) {
        return Interval(interval.Max / d, interval.Min / d);
    }
    throw "div zero error";
}

inline Interval operator/(double d, const Interval& interval) {
    if (interval.Max < 0 || interval.Min > 0) {
        if (d >= 0) {
            return Interval(d / interval.Max, d / interval.Min);        
        }
        return Interval(d / interval.Min, d / interval.Max);
    }
    throw "div zero error";
}

inline Interval sqr(const Interval& interval) {
    double d0 = interval.Min * interval.Min;
    double d1 = interval.Max * interval.Max;
    if (interval.Max < 0) {
        return Interval(d1, d0);
    }
    if (interval.Max < 0) {
        return Interval(d0, d1);
    }
    if (d0 < d1) {
        return Interval(0, d1);
    }
    return Interval(0, d0);
}

inline Interval sqrt(const Interval& interval) {
    if (interval.Min >= 0) {
        return Interval(sqrt(interval.Min), sqrt(interval.Max));
    }
    throw "sqrt error";
}

inline Interval cos(const Interval& interval) {
    double d = interval.Length();
	if (d >= PI * 2) {
		return Interval(-1, 1);
	}
	double min = interval.Min - int(interval.Min / (PI * 2)) * (PI * 2);
	if (min < 0) {
		min += PI * 2;
	}
	double max = min + d;
	if (min <= PI) {
		if (max <= PI) {
			return Interval(cos(max), cos(min));
		}
		if (max <= PI * 2) {
			double c0 = cos(min);
			double c1 = cos(max);
			return Interval(-1, c0 > c1 ? c0 : c1);
		}
		return Interval(-1, 1);
	} else {
		if (max < PI * 2) {
			return Interval(cos(min), cos(max));
		}
		if (max < PI * 3) {
			double c0 = cos(min)
			double c1 = cos(max)
			return Interval(c0 < c1 ? c0 : c1, 1)
		}
		return Interval(-1, 1)
	}
}

inline Interval sin(const Interval& interval) {
    return cos(interval - PI * 0.5);
}

inline void sincos(const Interval& interval, Interval* sin, Interval* cos) {
    *sin = sin(interval);
    *cos = cos(interval);
}

inline Interval::Interval() {
    Min = 0;
    Max = 0;
}

inline Interval::Interval(double d) {
    Min = d;
    Max = d;
}

inline Interval::Interval(double min, double max) {
    Min = min;
    Max = max;
}

inline bool Interval::IsIntersected(double d, double epsilon) const {
    return d <= Max + epsilon && d >= Min - epsilon;
}

inline bool Interval::IsIntersected(const Interval& interval, double epsilon) const {
    return interval.Min <= Max + epsilon && interval.Max >= Min - epsilon;
}


#endif