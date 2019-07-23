function [ output ] = centerDiff_2order( input, n, period )
%   input:
%       input --> 输入数据，单个列向量
%       n     --> 选用二次差分还是四次差分
%       period--> 差分周期，通常为控制周期
%   output：
%       output--> 经过滤波之后的数据，该数据为加速度量（即原数据的二阶导数），输出是单个列向量
    if n  ==  2
        len = length(input);
        outputTmp = zeros(len - 2, 1);
        for i = 1 : len - 2
            outputTmp(i) = (input(i + 2) - 2.0*input(i + 1) + input(i))/(period*period);
        end
    end
    if n  ==  4
        len = length(input);
        outputTmp = zeros(len - 4, 1);
        for i = 1 : len - 4
            outputTmp(i) = (-input(i + 4) + 16.0*input(i + 3) - 30.0*input(i + 2) + 16.0*input(i + 1) - input(i))/(12.0*period*period);
        end
    end
    output = outputTmp;

end

