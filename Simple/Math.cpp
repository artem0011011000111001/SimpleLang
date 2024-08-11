#include "Math.h"

#include <numeric>
#include <random>

using namespace Simple;

void Simple_libs::Math::Math::Init() {
	InitVars();
	InitFuncs();
}

void Simple_libs::Math::Math::InitVars() {
	_DEFINE_VAR_NUM(L"PI", MATH_PI, true);
	_DEFINE_VAR_NUM(L"E",  MATH_E,  true);
}

void Simple_libs::Math::Math::InitFuncs() {
    _DEFINE_FUNCTION(L"sin", [](Args_t args) {
        return NUMBER(std::sin(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"cos", [](Args_t args) {
        return NUMBER(std::cos(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"tan", [](Args_t args) {
        return NUMBER(std::tan(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"asin", [](Args_t args) {
        return NUMBER(std::asin(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"acos", [](Args_t args) {
        return NUMBER(std::acos(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"atan", [](Args_t args) {
        return NUMBER(std::atan(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"atan2", [](Args_t args) {
        return NUMBER(std::atan2(args[0]->AsDouble(), args[1]->AsDouble()));
        }, 2);

    _DEFINE_FUNCTION(L"sinh", [](Args_t args) {
        return NUMBER(std::sinh(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"cosh", [](Args_t args) {
        return NUMBER(std::cosh(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"tanh", [](Args_t args) {
        return NUMBER(std::tanh(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"power", [](Args_t args) {
        return NUMBER(std::pow(args[0]->AsDouble(), args[1]->AsDouble()));
        }, 2);

    _DEFINE_FUNCTION(L"sqrt", [](Args_t args) {
        return NUMBER(std::sqrt(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"cbrt", [](Args_t args) {
        return NUMBER(std::cbrt(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"abs", [](Args_t args) {
        return NUMBER(std::abs(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"round", [](Args_t args) {
        return NUMBER(std::round(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"ceil", [](Args_t args) {
        return NUMBER(std::ceil(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"floor", [](Args_t args) {
        return NUMBER(std::floor(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"exp", [](Args_t args) {
        return NUMBER(std::exp(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"log", [](Args_t args) {
        return NUMBER(std::log(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"log10", [](Args_t args) {
        return NUMBER(std::log10(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"factorial", [](Args_t args) {
        return NUMBER(_factorial(args[0]->AsDouble()));
        }, 1);

    _DEFINE_FUNCTION(L"comb", [](Args_t args) {
        int n = static_cast<int>(args[0]->AsDouble());
        int k = static_cast<int>(args[1]->AsDouble());
        if (k > n) {
            throw Simple_Error(L"k cannot be greater than n");
        }
        return NUMBER(_factorial(n) / (_factorial(k) * _factorial(n - k)));
        }, 2);

    _DEFINE_FUNCTION(L"perm", [](Args_t args) {
        int n = static_cast<int>(args[0]->AsDouble());
        int k = static_cast<int>(args[1]->AsDouble());
        if (k > n) {
            throw Simple_Error(L"k cannot be greater than n");
        }
        return NUMBER(_factorial(n) / _factorial(n - k));
        }, 2);

    _DEFINE_FUNCTION(L"mean", [](Args_t args) {
        std::vector<double> values;
        for (auto& val : args) {
            values.push_back(val->AsDouble());
        }
        return NUMBER(_mean(values));
        }, any_args);

    _DEFINE_FUNCTION(L"median", [](Args_t args) {
        std::sort(args.begin(), args.end(), [](const VALUE& val1, const VALUE& val2) {
            return val1->AsDouble() < val2->AsDouble();
            });
        size_t args_size = args.size();
        if (args_size % 2 == 0)
            return NUMBER((args[args_size / 2 - 1]->AsDouble() + args[args_size / 2]->AsDouble()) / 2);
        else
            return NUMBER(args[args_size / 2]->AsDouble());
        }, any_args);

    _DEFINE_FUNCTION(L"std_dev", [](Args_t args) {
        std::vector<double> values(args.size());
        std::transform(args.begin(), args.end(), values.begin(), [](const VALUE& val) {
            return val->AsDouble();
            });

        double m = _mean(values);
        double accum = 0.0;
        for (double value : values) {
            accum += (value - m) * (value - m);
        }
        return NUMBER(std::sqrt(accum / (values.size() - 1)));
        }, any_args);

    _DEFINE_FUNCTION(L"variance", [](Args_t args) {
        std::vector<double> values(args.size());
        std::transform(args.begin(), args.end(), values.begin(), [](const VALUE& val) {
            return val->AsDouble();
            });

        double m = _mean(values);
        double accum = 0.0;
        for (double value : values) {
            accum += (value - m) * (value - m);
        }
        return NUMBER(accum / (values.size() - 1));
        }, any_args);

    _DEFINE_FUNCTION(L"is_prime", [](Args_t args) {
        int n = static_cast<int>(args[0]->AsDouble());
        if (n <= 1) return FALSE;
        for (int i = 2; i <= std::sqrt(n); ++i) {
            if (n % i == 0) return FALSE;
        }
        return TRUE;
        }, 1);

    _DEFINE_FUNCTION(L"is_even", [](Args_t args) {
        int n = static_cast<int>(args[0]->AsDouble());
        return BOOL(n % 2 == 0);
        }, 1);

    _DEFINE_FUNCTION(L"is_odd", [](Args_t args) {
        int n = static_cast<int>(args[0]->AsDouble());
        return BOOL(n % 2 != 0);
        }, 1);
    
    _DEFINE_FUNCTION(L"random", BLOCK(args) {
        int min = (int)args[0]->AsDouble();
        int max = (int)args[1]->AsDouble();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(min, max);

        return NUMBER((double)dist(gen));
    }, 2);
}

double Simple_libs::Math::Math::_factorial(double n) {
	if (n < 0) {
		throw Simple_Error("Negative input in factorial");
	}
	return (n <= 1) ? 1 : n * _factorial(n - 1);
}

double Simple_libs::Math::Math::_mean(std::vector<double>& values) {
	return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
}