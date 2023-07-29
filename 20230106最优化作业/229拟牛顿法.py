'''
文档功能说明：使用拟牛顿法解决原料数量的份额分配问题
@2022308310229杨济嘉
@2023-01-06
'''
import sympy as sym # 导入函数化简和求导相关的库
import numpy as np # 导入numpy矩阵库
import matplotlib.pyplot as plt # 导入绘图库
import scipy.optimize as opt # 导入优化库

# 目标函数
def f(x): 
    return -0.00452*x**3 + 0.264*x**2 - 2.272*x + 10.2016 + 0.0052/x

# 绘制原始函数图像
def plot_origin(f): 
    x = np.linspace(0.01, 10, 1000) # 生成x轴数据
    y = f(x) # 计算y轴数据
    plt.plot(x, y) # 绘制函数图像
    plt.show() # 显示图像

# 优化并绘制函数图像
def optimize_and_plot(f, x_init, method, it): 
    a=np.linspace(0.001,10,1000)
    b=f(a)
    plt.plot(a,b)
    xi = [x_init] # 记录x的梯度下降情况
    res=opt.minimize(f,x0=xi[0],callback=xi.append,method=method,options={'maxiter':it}) # 调用最优化方法进行求解
    plt.plot(xi[:],[f(xi[i]) for i in range(len(xi))],'o-')
    print(res) # 打印优化结果
    plt.show() # 显示图像

if __name__ == '__main__':
    x = sym.symbols('x') # 定义变量x

    sym_f = sym.simplify(
        (0.08*x**2+0.1*x+0.32+0.004*(10-x)**3+0.09*(10-x)**2+0.1*(10-x))*0.48+
        (0.09*x**2+0.01*x**-1+0.08+0.005*(10-x)**3+0.1*(10-x)+0.32)*0.52
    ) # 声明对应的目标函数
    print(sym_f) # 打印化简后的目标函数

    plot_origin(f) # 绘制原始函数图像

    # 使用两种不同的最优化算法，对每种算法设置不同的迭代次数的参数，并且进行绘图
    methods = ['BFGS', 'SLSQP']
    iters = [1, 2, 5, 10]
    for method in methods:
        for it in iters:
            x_init = np.random.rand(1) # 随机生成初始点
            print(f'本次循环中，使用的最优化方法是{method},最大收敛迭代次数设置为{it},得到的结果和图像如下：')
            optimize_and_plot(f, x_init, method, it)
            print('-------------------------------------------')


'''
'''
