function [ output ] = centerDiff_2order( input, n, period )
%   input:
%       input --> �������ݣ�����������
%       n     --> ѡ�ö��β�ֻ����Ĵβ��
%       period--> ������ڣ�ͨ��Ϊ��������
%   output��
%       output--> �����˲�֮������ݣ�������Ϊ���ٶ�������ԭ���ݵĶ��׵�����������ǵ���������
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

