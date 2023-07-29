### packages ###
library(readxl) #读取Excel文件数据
library(dplyr) #数据处理和操作，包括数据筛选、变换、聚合等
library(lubridate) #处理日期和时间数据
library(xts) #处理时间序列数据
library(forecast) #时间序列分析
library(randomForest) #随机森林
library(PerformanceAnalytics) #投资组合分析，包括计算收益率、风险评估、回测等
library(portfolio) #投资组合管理和优化，包括构建投资组合、计算风险和收益等
library(quantmod) #获取和分析金融数据，包括股票价格数据获取、技术指标计算等
library(ggplot2) #数据可视化和绘图
library(gridExtra) #排列和组合多个图表



### read data ###
#data <- read_excel("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx")

stock01<-read_xlsx("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx",sheet=1)
str(stock01)
#stock01$时间 <- as.Date(as.numeric(stock01$时间), origin = "1899-12-30") #这句只需要执行一次就行了，第二次得注释掉
#str(stock01)
summary(stock01)
stock02<-read_xlsx("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx",sheet=3)
#stock02$时间 <- as.Date(as.numeric(stock02$时间), origin = "1899-12-30")
str(stock02)
summary(stock02)
stock03<-read_xlsx("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx",sheet=3)
#stock03$时间 <- as.Date(as.numeric(stock03$时间), origin = "1899-12-30")
str(stock03)
summary(stock03)
stock04<-read_xlsx("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx",sheet=4)
#stock04$时间 <- as.Date(as.numeric(stock04$时间), origin = "1899-12-30")
str(stock04)
summary(stock04)
stock05<-read_xlsx("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx",sheet=5)
#stock05$时间 <- as.Date(as.numeric(stock05$时间), origin = "1899-12-30")
str(stock05)
summary(stock05)
stock06<-read_xlsx("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx",sheet=6)
#stock06$时间 <- as.Date(as.numeric(stock06$时间), origin = "1899-12-30")
str(stock06)
summary(stock06)
stock07<-read_xlsx("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx",sheet=7)
#stock07$时间 <- as.Date(as.numeric(stock07$时间), origin = "1899-12-30")
str(stock07)
summary(stock07)
stock08<-read_xlsx("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx",sheet=8)
#stock08$时间 <- as.Date(as.numeric(stock08$时间), origin = "1899-12-30")
str(stock08)
summary(stock08)
stock09<-read_xlsx("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx",sheet=9)
#stock09$时间 <- as.Date(as.numeric(stock09$时间), origin = "1899-12-30")
str(stock09)
summary(stock09)
stock10<-read_xlsx("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx",sheet=10)
#stock10$时间 <- as.Date(as.numeric(stock10$时间), origin = "1899-12-30")
str(stock10)
summary(stock10)
stock11<-read_xlsx("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx",sheet=11)
#stock11$时间 <- as.Date(as.numeric(stock11$时间), origin = "1899-12-30")
str(stock11)
summary(stock11)
stock12<-read_xlsx("D:/ArineCollection/2023CAUt2/course08DataMining/expt-group/HistoryData3_work.xlsx",sheet=12)
#stock12$时间 <- as.Date(as.numeric(stock12$时间), origin = "1899-12-30")
str(stock12)
summary(stock12)

stocks <- rbind(stock01, stock02, stock03, stock04, stock05, stock06, stock07, stock08, stock09, stock10, stock11, stock12)
names(stock01)
names(stocks)
str(stocks)
summary(stocks)
#theme_set(theme_bw())

#合并向量
股票 <- c(rep("保利联合", nrow(stock01)),
        rep("以岭药业", nrow(stock02)),
        rep("中国石化", nrow(stock03)),
        rep("南方航空", nrow(stock04)),
        rep("中国联通", nrow(stock05)),
        rep("中国建筑", nrow(stock06)),
        rep("永辉超市", nrow(stock07)),
        rep("贵州茅台", nrow(stock08)),
        rep("平安银行", nrow(stock09)),
        rep("万科A", nrow(stock10)),
        rep("神州高铁", nrow(stock11)),
        rep("深物业A", nrow(stock12)))
stocks$股票<-股票
df <- stocks



### visualizing ###

#按照收盘价分类股票
class1 <- df %>% group_by(股票) %>% filter(max(收盘价) >= 100)
class2 <- df %>% group_by(股票) %>% filter(max(收盘价) > 20 & max(收盘价) < 100)
class3 <- df %>% group_by(股票) %>% filter(max(收盘价) <= 20)
class1
class2
class3

# plot
plot1 <- ggplot(class1, aes(x = 时间)) +
  geom_line(aes(y = 收盘价, col = 股票)) +
  labs(title = "第一类股票收盘价时序图",
       subtitle = "第一类股票：收盘价大于等于100的股票",
       caption = "数据挖掘",
       y = "收盘价",
       color = "股票名称") +
  theme(axis.text.x = element_text(angle = 0, vjust = 0.5, size = 8),
        panel.grid.minor = element_blank())
plot2 <- ggplot(class2, aes(x = 时间)) +
  geom_line(aes(y = 收盘价, col = 股票)) +
  labs(title = "第二类股票收盘价时序图",
       subtitle = "第二类股票：收盘价在20至100之间的股票",
       caption = "数据挖掘",
       y = "收盘价",
       color = "股票名称") +
  theme(axis.text.x = element_text(angle = 0, vjust = 0.5, size = 8),
        panel.grid.minor = element_blank())
plot3 <- ggplot(class3, aes(x = 时间)) +
  geom_line(aes(y = 收盘价, col = 股票)) +
  labs(title = "第三类股票收盘价时序图",
       subtitle = "第三类股票：收盘价小于等于20的股票",
       caption = "数据挖掘",
       y = "收盘价",
       color = "股票名称") +
  theme(axis.text.x = element_text(angle = 0, vjust = 0.5, size = 8),
        panel.grid.minor = element_blank())
grid.arrange(plot1, plot2, plot3, ncol = 1) # Combine the plots
#grid.arrange(plot1, plot2, plot3, plot4, ncol = 2, nrow = 2) # Combine the plots


# 股票stock08参数随时间变化的趋势
grid.arrange(
  ggplot(stock08, aes(x = 时间)) +
    geom_line(aes(y = 开盘价, col = "开盘价")) +
    geom_line(aes(y = 收盘价, col = "收盘价")) +
    geom_line(aes(y = 最高价, col = "最高价")) +
    geom_line(aes(y = 最低价, col = "最低价")) +
    geom_line(aes(y = 前收盘价, col = "前收盘价")) +
    geom_line(aes(y = 均价, col = "均价")) +
    labs(title = "贵州茅台股票价格随时间的变化趋势",
         x = "时间",
         y = "参数值",
         color = "参数") +
    theme_bw(),
  
  ggplot() +
    geom_line(data = stock08, aes(x = 时间, y = 成交量, col = "成交量")) +
    geom_line(data = stock08, aes(x = 时间, y = 成交金额 / 1000, col = "成交金额（千）")) +
    labs(title = "贵州茅台成交量和成交金额随时间的变化趋势",
         x = "时间",
         y = "参数值",
         color = "参数") +
    theme_bw(),
  
  ggplot(stock08, aes(x = 时间)) +
    geom_line(aes(y = 涨跌, col = "涨跌")) +
    geom_line(aes(y = 涨跌幅, col = "涨跌幅")) +
    geom_line(aes(y = 换手率, col = "换手率")) +
    geom_line(aes(y = 振幅, col = "振幅")) +
    labs(title = "贵州茅台其他参数随时间的变化趋势",
         x = "时间",
         y = "参数值",
         color = "参数") +
    theme_bw(),
  
  ncol = 1
)

### calculating ###

# 计算收益率
stock01_close <- as.xts(stock01$收盘价, stock01$时间)
stock02_close <- as.xts(stock02$收盘价, stock02$时间)
stock03_close <- as.xts(stock03$收盘价, stock03$时间)
stock04_close <- as.xts(stock04$收盘价, stock04$时间)
stock05_close <- as.xts(stock05$收盘价, stock05$时间)
stock06_close <- as.xts(stock06$收盘价, stock06$时间)
stock07_close <- as.xts(stock07$收盘价, stock07$时间)
stock08_close <- as.xts(stock08$收盘价, stock08$时间)
stock09_close <- as.xts(stock09$收盘价, stock09$时间)
stock10_close <- as.xts(stock10$收盘价, stock10$时间)
stock11_close <- as.xts(stock11$收盘价, stock11$时间)
stock12_close <- as.xts(stock12$收盘价, stock12$时间)
stock01_return <- CalculateReturns(stock01_close)[-1]
stock02_return <- CalculateReturns(stock02_close)[-1]
stock03_return <- CalculateReturns(stock03_close)[-1]
stock04_return <- CalculateReturns(stock04_close)[-1]
stock05_return <- CalculateReturns(stock05_close)[-1]
stock06_return <- CalculateReturns(stock06_close)[-1]
stock07_return <- CalculateReturns(stock07_close)[-1]
stock08_return <- CalculateReturns(stock08_close)[-1]
stock09_return <- CalculateReturns(stock09_close)[-1]
stock10_return <- CalculateReturns(stock10_close)[-1]
stock11_return <- CalculateReturns(stock11_close)[-1]
stock12_return <- CalculateReturns(stock12_close)[-1]


#收益率计算和可视化：茅台
stock08$收益率 <- c(0, diff(stock08$收盘价)/stock08$收盘价[-length(stock08$收盘价)]) # Compute % Returns
ggplot(stock08, aes(时间, 收益率)) + 
  geom_area() + 
  theme(axis.text.x = element_text()) + 
  labs(title="收益率时序图", 
       subtitle = "以一类股票贵州茅台为例", 
       y="收益率", 
       caption="数据挖掘")   
stock08%>%
  group_by(年月=as.yearmon(时间))%>%
  summarise(月累计收益率=sum(收益率))

#计算股票数据的收益率和累计收益率
stock01$收益率 <- c(0, as.numeric(stock01_return))
stock01$累计收益率 <- cumsum(stock01$收益率)
stock02$收益率 <- c(0, as.numeric(stock02_return))
stock02$累计收益率 <- cumsum(stock02$收益率)
stock03$收益率 <- c(0, as.numeric(stock03_return))
stock03$累计收益率 <- cumsum(stock03$收益率)
stock04$收益率 <- c(0, as.numeric(stock04_return))
stock04$累计收益率 <- cumsum(stock04$收益率)
stock05$收益率 <- c(0, as.numeric(stock05_return))
stock05$累计收益率 <- cumsum(stock05$收益率)
stock06$收益率 <- c(0, as.numeric(stock06_return))
stock06$累计收益率 <- cumsum(stock06$收益率)
stock07$收益率 <- c(0, as.numeric(stock07_return))
stock07$累计收益率 <- cumsum(stock07$收益率)
stock08$收益率 <- c(0, as.numeric(stock08_return))
stock08$累计收益率 <- cumsum(stock08$收益率)
stock09$收益率 <- c(0, as.numeric(stock09_return))
stock09$累计收益率 <- cumsum(stock09$收益率)
stock10$收益率 <- c(0, as.numeric(stock10_return))
stock10$累计收益率 <- cumsum(stock10$收益率)
stock11$收益率 <- c(0, as.numeric(stock11_return))
stock11$累计收益率 <- cumsum(stock11$收益率)
stock12$收益率 <- c(0, as.numeric(stock12_return))
stock12$累计收益率 <- cumsum(stock12$收益率)


#收益率对比
par(mfrow=c(4,3))
plot(stock01$收益率, type="l", xlab="时间轴", ylab="收益率", main="保利联合")
plot(stock02$收益率, type="l", xlab="时间轴", ylab="收益率", main="以岭药业")
plot(stock03$收益率, type="l", xlab="时间轴", ylab="收益率", main="中国石化")
plot(stock04$收益率, type="l", xlab="时间轴", ylab="收益率", main="南方航空")
plot(stock05$收益率, type="l", xlab="时间轴", ylab="收益率", main="中国联通")
plot(stock06$收益率, type="l", xlab="时间轴", ylab="收益率", main="中国建筑")
plot(stock07$收益率, type="l", xlab="时间轴", ylab="收益率", main="永辉超市")
plot(stock08$收益率, type="l", xlab="时间轴", ylab="收益率", main="贵州茅台")
plot(stock09$收益率, type="l", xlab="时间轴", ylab="收益率", main="平安银行")
plot(stock10$收益率, type="l", xlab="时间轴", ylab="收益率", main="万科A")
plot(stock11$收益率, type="l", xlab="时间轴", ylab="收益率", main="神州高铁")
plot(stock12$收益率, type="l", xlab="时间轴", ylab="收益率", main="深物业A")

#累计收益率对比
par(mfrow=c(1,1))
plot(stock01$累计收益率, type="l", ylim=c(-0.5, 1.5), xlab="时间轴", ylab="累计收益率")
lines(stock02$累计收益率, col=2, lty=2)
lines(stock03$累计收益率, col=3, lty=3)
lines(stock04$累计收益率, col=4, lty=4)
lines(stock05$累计收益率, col=5, lty=5)
lines(stock06$累计收益率, col=6, lty=6)
lines(stock07$累计收益率, col=7, lty=7)
lines(stock08$累计收益率, col=8, lty=8)
lines(stock09$累计收益率, col=9, lty=9)
lines(stock10$累计收益率, col='grey', lty=10)
lines(stock11$累计收益率, col='purple', lty=11)
lines(stock12$累计收益率, col='brown', lty=12)
legend("topleft", col=c(1:12, "grey", "purple", "brown"), lty=1:13,
       legend=c("保利联合", "以岭药业", "中国石化", "南方航空", "中国联通",
                "中国建筑", "永辉超市", "贵州茅台", "平安银行", "万科A",
                "神州高铁", "深物业A"),
       cex=0.7)


#各股重要指标
tdays <- 244  #我们的数据中交易日数量为244
stocks <- rbind(stock01, stock02, stock03, stock04, stock05, stock06, stock07, stock08, stock09, stock10, stock11, stock12)
stocks$股票<-股票
stock_info<-stocks%>%
  group_by(股票)%>%
  summarise(平均年化收益率=mean(收益率)*tdays,年化收益波动率=sd(收益率)*sqrt(tdays),
            累计收益率=sum(收益率))
stock_info
data.frame(stock_info)

#计算投资组合的预期收益率和收益率波动率
weight =  1/12  #假设每个股票在投资组合中权重相等
equal_w_result<-mean(stock_info$平均年化收益率) #等权重下的投资组合的预期收益率
equal_w_result
mean(stock_info$累计收益率)
stocks_cov <- cov(data.frame(stock01$收益率, stock02$收益率, stock03$收益率, stock04$收益率, stock05$收益率,
                             stock06$收益率, stock07$收益率, stock08$收益率, stock09$收益率, stock10$收益率,
                             stock11$收益率, stock12$收益率)) * 252
equal_w_vol <- sqrt(t(rep(weight, 12)) %*% stocks_cov %*% rep(weight, 12)) #投资组合的收益率波动率
equal_w_vol
R_mean <- stock_info$平均年化收益率



#### portfolio ####

# 绘制可行集
Rt = c()   #初始化投资组合收益率
Vl = c()   #初始化投资组合收益波动率
x = replicate(10000,{runif(12,0,1)}) #生成10000个不同权重的预期收益率和收益波动率
x = (matrix(unlist(x), nrow = 10000, ncol = 12, byrow = TRUE)) #修改权重矩阵的维度
head(x)
sum(x[1,]/sum(x[1,]))
i=1:10000
weight = x[i,]/apply(x[i,],1,sum) #标准化权重矩阵：将权重矩阵x的每一行除以该行权重之和，以确保每个投资组合的权重之和为1
head(weight)
apply(weight,1,sum)
for(i in 1:10000){
  Rt[i]=sum(weight[i,]*R_mean)
  Vl[i]=sqrt(weight[i,]%*%stocks_cov%*%weight[i,])
  Rt=c(Rt,Rt[i])
  Vl=c(Vl,(Vl[i]))
}#投资组合收益率和波动率
plot(equal_w_vol,equal_w_result,xlim=c(min(Vl),max(Vl)),ylim=c(min(Rt),max(Rt)),ylab="收益率",xlab="波动率",pch=8)
points(Vl,Rt,pch=20,col=2)
abline(h=0,lty=2)
num_low<-data.frame(Vl,Rt)%>%filter(Rt>0)
num_low<-which(Vl==min(num_low$Vl))
points(equal_w_vol,equal_w_result,pch=8)
points(Vl[num_low],Rt[num_low],pch=15,col=3)
points(Vl[which(Rt==max(Rt))],max(Rt),pch=17,col=4)
legend("topleft", col = c(1, 3, 4), pch = c(8, 15, 17),
       legend = c("等权分配下的投资组合", "最低风险投资组合", "最优投资组合"),
       cex = 1, bty = "n", bg = "transparent")


## 提取投资组合参数

#最低风险投资组合
low_risk_comb<-data.frame(波动率=Vl[num_low],收益率=Rt[num_low],t(data.frame(最低风险投资组合=weight[which(Vl==min(Vl)),])))
colnames(low_risk_comb)[3:14] <- c(
  "保利联合", "以岭药业", "中国石化", "南方航空", "中国联通", "中国建筑",
  "永辉超市", "贵州茅台", "平安银行", "万科A", "神州高铁", "深物业A"
)
#round(low_risk_comb,3) #四舍五入，保留三位小数

#最优投资组合
best_comb<-data.frame(波动率=Vl[which(Rt==max(Rt))],
                      收益率=max(Rt),t(data.frame(最优投资组合=weight[which(Rt==max(Rt)),])))
colnames(best_comb)[3:14] <- c(
  "保利联合", "以岭药业", "中国石化", "南方航空", "中国联通", "中国建筑",
  "永辉超市", "贵州茅台", "平安银行", "万科A", "神州高铁", "深物业A"
)

#等权分配下的投资组合
equal_w_comb <- data.frame(equal_w_vol, equal_w_result, t(rep(1/12, 12)))
colnames(equal_w_comb) <- colnames(best_comb)
rownames(equal_w_comb) <- "等权分配下的投资组合"
rbind(best_comb,low_risk_comb,equal_w_comb)
comb_result<-round(rbind(equal_w_comb,low_risk_comb,best_comb),4)
comb_result

### save data ###
#write.csv(comb_result, file = "my_portfolio.csv", row.names = FALSE)
#print("Result saved to csv file.")




### eval ###

returns <- data.frame(stock01$收益率, stock02$收益率, stock03$收益率, stock04$收益率, stock05$收益率, stock06$收益率,
                      stock07$收益率, stock08$收益率, stock09$收益率, stock10$收益率, stock11$收益率, stock12$收益率)

#最优投资组合
comb_1<-Return.portfolio(as.xts(returns,stock01$时间),weights = weight[which(Rt==max(Rt)),])
plot(cumsum(comb_1),main="各投资组合累计收益率",col=4,lwd=1)
#最低风险投资组合
comb_2<-Return.portfolio(as.xts(returns,stock01$时间),weights = weight[which(Vl==Vl[num_low]),])
lines(cumsum(comb_2),col=3)
#等权分配下的投资组合
comb_3<-Return.portfolio(as.xts(returns,stock01$时间),weights = rep(1/12,12))
lines(cumsum(comb_3),col=1)

#夏普比率：通过将平均超额收益减去无风险利率，然后除以波动率
comb_table<-t(cbind(table.AnnualizedReturns(comb_1),table.AnnualizedReturns(comb_2),table.AnnualizedReturns(comb_3)))
rownames(comb_table)<-c("最优投资组合","最低风险投资组合","等权分配下的投资组合")
comb_table

#超额收益率计算
market_return <- apply(data.frame(stock01$收益率, stock02$收益率, stock03$收益率, stock04$收益率, stock05$收益率,
                                  stock06$收益率, stock07$收益率, stock08$收益率, stock09$收益率, stock10$收益率,
                                  stock11$收益率, stock12$收益率), 1, mean)

#市场收益率（12支股票当日平均收益率)
mean(comb_1-market_return)#平均超额收益
ex_sum1<-sum(comb_1-market_return)#累计超额收益率
ex_sum2<-sum(comb_2-market_return)
mean(comb_2-market_return)
ex_sum3<-sum(comb_3-market_return)
mean(comb_3-market_return)

m1<-data.frame(期望损失=t(ES(comb_1,p=0.95,method="historical")),最大回撤=maxDrawdown(comb_1,geometric = TRUE),
               平均超额收益=mean(comb_1-market_return))
m2<-data.frame(期望损失=t(ES(comb_2,p=0.95,method="historical")),最大回撤=maxDrawdown(comb_2,geometric = TRUE),
               平均超额收益=mean(comb_2-market_return))
m3<-data.frame(期望损失=t(ES(comb_3,p=0.95,method="historical")),最大回撤=maxDrawdown(comb_3,geometric = TRUE),
               平均超额收益=mean(comb_3-market_return))
cbind(comb_table, rbind(m1, m2, m3))




### random forest ###

#投资组合灵敏度分析
fit.test<-randomForest(Rt~Vl)

newVl<-seq(min(Vl),max(Vl),0.00001)
pred.rt<-predict(fit.test,data.frame(Vl=newVl))
testdata<-data.frame(newVl,pred.rt)
datatest<-data.frame(Vl,Rt)
p1=ggplot(testdata,aes(newVl,pred.rt))+geom_point(col="skyblue",shape=20)+theme_minimal()+
  geom_smooth(method="loess")+xlab("波动率")+ylab("收益率")+labs(caption = "数据：基于随机森林模型的灵敏度分析结果")
p2=ggplot(datatest,aes(Vl,Rt))+geom_point(col="skyblue",shape=20)+theme_minimal()+
  geom_smooth(method="loess")+xlab("波动率")+ylab("收益率")+labs(caption = "数据：10000种投资组合结果")
grid.arrange(p1,p2,ncol=2)


#基于最优投资组合的上周平均收益率与及各股收盘价等参数进行机器学习
best_weights = weight[which(Rt==max(Rt)),]
#资产分配（市值分配）
mystock <- stock01[, -1] * best_weights[1] +
  stock02[, -1] * best_weights[2] +
  stock03[, -1] * best_weights[3] +
  stock04[, -1] * best_weights[4] +
  stock05[, -1] * best_weights[5] +
  stock06[, -1] * best_weights[6] +
  stock07[, -1] * best_weights[7] +
  stock08[, -1] * best_weights[8] +
  stock09[, -1] * best_weights[9] +
  stock10[, -1] * best_weights[10] +
  stock11[, -1] * best_weights[11] +
  stock12[, -1] * best_weights[12]

mystock$交易日<-1:nrow(mystock) #244
mystock$当日涨跌<-ifelse(mystock$收益率>=0,1,0) #根据当日的收益率来判断股票是涨（1）还是跌（0）

#上周平均收益率(一周5个交易日)
rt_last_week<-cumsum(mystock$收益率[1:4])
for(i in 1:(nrow(mystock)-4)){
  ma5<-mean(mystock$收益率[i:(i+4)])
  rt_last_week<-append(rt_last_week,ma5)
}
mystock$上周平均收益率<-rt_last_week
#write.csv(mystock,"best_portfolio.csv") #最优投资组合参数

rf1<-randomForest(收盘价~开盘价+最高价+最低价+成交量+上周平均收益率,data=mystock[1:200,])
pred80<-predict(rf1,mystock[201:244,])
plot(mystock[201:244,7],type="l") #第7列成交量
lines(pred80,col=2)#样本外预测
plot(mystock$收盘价[1:200],type="l",lwd=1.5)
lines(rf1$predicted,col=2,lwd=1.7)#样本内预测
mean(rf1$mse) #随机森林模型的MSE


# visualizing
plot(mystock$收盘价[1:200],type="l",xlim = c(1,244),ylim = c(min(mystock$收盘价),max(mystock$收盘价)),
     xlab="交易日",ylab="收盘价")
lines(rf1$predicted,col=2)
lines(201:244,mystock[201:244,2],col=4)#参数：第2列收盘价
lines(201:244,pred80,col="orange",lwd=2)
abline(v=201,lty=4)#垂直参考线的位置为201
text(100,110,"训练集")
text(222,110,"测试集")
rmse1<-sqrt(mean((rf1$predicted-mystock$收盘[1:200])^2))##均方根误差
rmse2<-sqrt(mean((pred80-mystock$收盘[201:244])^2))
mae1<-mean(abs(rf1$predicted-mystock$收盘[1:200]));mae1##平均绝对误差
mae2<-mean(abs(pred80-mystock$收盘[201:244]));mae2
text(100,105,paste0("RMSE:",round(rmse1,3)))
text(225,105,paste0("RMSE:",round(rmse2,3)))
text(100,100,paste0("MAE:",round(mae1,3)))
text(225,100,paste0("MAE:",round(mae2,3)))
legend("topleft", col = c(1, 2, 4, 'orange'), lwd = c(1, 1, 1, 2),
       legend = c("测试集原序列", "模型样本内预测结果", "测试集原序列", "模型样本外预测结果"),
       cex = 0.8, bty = "n", bg = "transparent")  # 调整图例

### prediction ###

# Holt-Winters
#par(mfrow=c(2,3))
#收盘价
x.fit.close<-HoltWinters(mystock$收盘价,gamma = F)
x.fore.close <- forecast(x.fit.close, h = 61)
future.close<-x.fore.close$mean
#开盘价
x.fit.open<-HoltWinters(mystock$开盘价,gamma = F)
x.fore.open<-forecast(x.fit.open,h=61)
future.open<-x.fore.open$mean
#最高价
x.fit.high<-HoltWinters(mystock$最高价,gamma = F)
x.fore.high<-forecast(x.fit.high,h=61)
future.high<-x.fore.high$mean
#最低价
x.fit.low<-HoltWinters(mystock$最低价,gamma = F)
x.fore.low<-forecast(x.fit.low,h=61)
future.low<-x.fore.low$mean
#成交量
x.fit.vol<-HoltWinters(mystock$成交量,gamma = F)
#plot(x.fit.vol)
x.fore.vol<-forecast(x.fit.vol,h=61)
future.vol<-x.fore.vol$mean
#上周平均收益率
x.fit.last<-HoltWinters(mystock$上周平均收益率,gamma = F)
x.fore.last<-forecast(x.fit.last,h=61)
future.last<-x.fore.last$mean


# predicting
future.stock<-data.frame(开盘价=future.open,最高价=future.high,最低价=future.low,成交量=future.vol,
                         上周平均收益率=future.last)
rf.fit<-randomForest(收盘价~开盘价+最高价+最低价+成交量+上周平均收益率,data=mystock)
rf.fit
future.pred<-predict(rf.fit,future.stock)

par(mfrow=c(1,2))
plot(245:(244+61),future.pred,type="l",lwd=0.5,lty=5,xlab="交易日",ylab="收盘价")
points(245:(244+61),future.pred,col=2,pch=3,cex=0.2)
plot(c(mystock$收盘,future.pred),type="l",xlab="交易日",ylab="收盘价")
lines(245:(244+61),future.pred,type="l",col="orange",lwd=2)
abline(v=244,lty=4)
text(150,200,"历史244个交易日实际数据")
text(270,200,"未来61个交易日预测数据")

