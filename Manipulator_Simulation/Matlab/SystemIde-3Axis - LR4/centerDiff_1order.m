function [ output ] = centerDiff_1order( input, n, period)
%   input:
%       input --> 输入数据，单个列向量
%       n     --> 选用二次差分还是四次差分
%       period--> 差分周期，通常为控制周期
%   output：
%       output--> 经过滤波之后的数据，该数据为速度量（即原数据的一阶导数），输出是单个列向量
    if n  ==  2
        len = length(input);
        outputTmp = zeros(len - 2, 1);
        for i = 1 : len - 2
            outputTmp(i) = (input(i + 2) - input(i))/(2.0*period);
        end
    end
    if n  ==  4
        len = length(input);
        outputTmp = zeros(len - 4, 1);
        for i = 1 : len - 4
            outputTmp(i) = (-input(i + 4) + 8.0*input(i + 3) - 8.0*input(i + 1) + input(i))/(12.0*period);
        end
    end
    output = outputTmp;
end

