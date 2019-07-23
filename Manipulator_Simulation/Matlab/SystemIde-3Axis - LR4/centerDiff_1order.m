function [ output ] = centerDiff_1order( input, n, period)
%   input:
%       input --> �������ݣ�����������
%       n     --> ѡ�ö��β�ֻ����Ĵβ��
%       period--> ������ڣ�ͨ��Ϊ��������
%   output��
%       output--> �����˲�֮������ݣ�������Ϊ�ٶ�������ԭ���ݵ�һ�׵�����������ǵ���������
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

