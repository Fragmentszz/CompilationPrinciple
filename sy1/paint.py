from snapshot_selenium import snapshot as driver

from pyecharts import options as opts
from pyecharts.charts import Bar,Graph
from pyecharts.render import make_snapshot
from pyecharts.globals import CurrentConfig
import os
import sys


CurrentConfig.ONLINE_HOST = "./";
def bar_chart() -> Bar:
    c = (
        Bar()
        .add_xaxis(["衬衫", "毛衣", "领带", "裤子", "风衣", "高跟鞋", "袜子"])
        .add_yaxis("商家A", [114, 55, 27, 101, 125, 27, 105])
        .add_yaxis("商家B", [57, 134, 137, 129, 145, 60, 49])
        .reversal_axis()
        .set_series_opts(label_opts=opts.LabelOpts(position="right"))
        .set_global_opts(title_opts=opts.TitleOpts(title="Bar-测试渲染图片"))
    )
    return c

def graph_chart(nodes,edges) -> Graph:
    c = (
        Graph(init_opts=opts.InitOpts(width="1440px",height="1080px")).add(
            "自动机图示",nodes,edges,layout="force", repulsion = 5000,edge_symbol=["none","arrow"]
        )
    )
    # 设置全局参数，如标题等
    c.set_global_opts(title_opts=opts.TitleOpts(title="自动机图示"))
    return c
if __name__ == '__main__':
    txtname = sys.argv[1]
    print(txtname)
    nodes = []
    edges = []
    haveedge = []
    with open(txtname,'r') as fp:
        firstline = fp.readline().strip('\n').split(' ')
        print(firstline)
        n = eval(firstline[0])
        m = eval(firstline[1])
        p = eval(firstline[2])
        q = eval(firstline[3])
        t = eval(firstline[4])
        for i in range(n):
            nodes.append({"name":str(i),"symbolSize": 50})
            haveedge.append([])
            for j in range(n):
                haveedge[i].append(-1)
        Sigma = fp.readline().strip().split(' ')
        print(Sigma)
        for i in range(p):
            edge = fp.readline().strip().split(' ')
            u = eval(edge[1])
            v = eval(edge[2])
            c = eval(edge[0])
            cc = 0.2
            haveedge[u][v] = c
        for i in range(n):
            for j in range(n):
                if(haveedge[i][j] != -1):
                    cc = 0
                    if(haveedge[j][i] != -1):
                        cc = 0.4
                    edges.append({"source":nodes[i].get('name'),
                          "target":nodes[j].get('name'),
                          "label":{"show":True,"formatter":Sigma[haveedge[i][j]]},
                          "lineStyle":{"width":3,"curveness":cc}
                          })
        S = []
        S_l = fp.readline().strip().split(' ')
        for i in range(q):
            S.append(eval(S_l[i]))
        Z = []
        Z_l = fp.readline().strip().split(' ')
        for i in range(t):
            Z.append(eval(Z_l[i]))
        print(edges)
        print(S)
        print(Z)
    # # 需要安装 snapshot-selenium 或者 snapshot-phantomjs
    # make_snapshot(driver, bar_chart().render(), "bar.png")
    htmlname = graph_chart(nodes,edges).render("./html/render.html")

    os.system(htmlname)