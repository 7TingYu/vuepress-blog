---
title: vue next - 村长源码共读会 初始化流程
date: 2022-3-6
tags:
 - vue
categories:
 - vue
---



## 源码学习方法

- 通过实践梳理要做的主线去读源码
- 画思维导图（我选择写文档）
- 提问题，源码中找答案
- 造轮子
- 费曼学习法（学-用-教）



## 主线

1. App 实例如何创建 -- createApp()
2. 挂载 -- mount('#app')



## 调试环境

- 克隆项目

  - git@github.com:vuejs/core.git

- 安装依赖

  - ```shell
  	# 安装 vue3 配置环境
    npm i pnpm -g
    # package 中删除 pupteer 依赖
    pnpm i
    ```

- 配置脚本

  - ```json
    {"dev": "node scripts/dev.js --soursemap"}
    ```

- 打包

  - ```
    pnpm dev



判断是否打包成功

> .\packages\vue\dist 是否存在
>
> .\packages\vue\examples 测试样例



## 整体结构

vue 主依赖于

- compiler-dom
- runtime-dom 扩展浏览器平台
  - runtime-core -- vue 通用代码
- reactivity





## 初始化流程

### 主线

**实例创建过程**

createApp()

**挂载过程**

app.mount()



### 学习方法

**单步调试**

### 单步调试

借助浏览器从前往后调试

vue 工作方式：组件 => 组件实例 => render() => vnode => patch() => dom

```js
function baseCreateRenderer(
  options: RendererOptions,
  createHydrationFns?: typeof createHydrationFunctions
): any {
    // ...
	// packages\runtime-core\src\renderer.ts # 2335 
    return {
        // 接收 vdom 转换为 dom，追加到宿主元素
        render,
        // ssr，服务端讲一个 vnode 生成 html
        hydrate,
        // 创建 app 实例
        createApp: createAppAPI(render, hydrate)
    }
}
// packages\runtime-core\src\apiCreateApp.ts # 117 
export function createAppAPI<HostElement>(
  render: RootRenderFunction,
  hydrate?: RootHydrateFunction
): CreateAppFunction<HostElement> {
  // 用户创建的 App 实例
  return function createApp(rootComponent, rootProps = null) {
	// ...
    const context = createAppContext()
    const installedPlugins = new Set()

    let isMounted = false

    const app: App = (context.app = {
      // ...

      get config() {
        return context.config
      },

      set config(v) {
        // ...
      },

      // vue2 挂载在构造函数上
      use(plugin: Plugin, ...options: any[]) {
        // ...
      },

      mixin(mixin: ComponentOptions) {
        // ...
      },

      component(name: string, component?: Component): any {
        // ...
      },

      directive(name: string, directive?: Directive) {
        // ...
      },

      mount(
        rootContainer: HostElement, // 宿主元素
        isHydrate?: boolean,
        isSVG?: boolean
      ): any {
        // 首次未执行，并未挂载
        if (!isMounted) {
          const vnode = createVNode(
            rootComponent as ConcreteComponent,
            rootProps
          )
          // store app context on the root VNode.
          // this will be set on the root instance on initial mount.
          vnode.appContext = context

          // HMR root reload
          if (__DEV__) {
            context.reload = () => {
              render(cloneVNode(vnode), rootContainer, isSVG)
            }
          }

          // 创建根组件虚拟 dom
          if (isHydrate && hydrate) {
            hydrate(vnode as VNode<Node, Element>, rootContainer as any)
          } else {
            // 渲染 vnode -> dom -> rootContainer
            render(vnode, rootContainer, isSVG)
          }
          isMounted = true
          app._container = rootContainer
          // for devtools and telemetry
          ;(rootContainer as any).__vue_app__ = app

          if (__DEV__ || __FEATURE_PROD_DEVTOOLS__) {
            app._instance = vnode.component
            devtoolsInitApp(app, version)
          }

          return getExposeProxy(vnode.component!) || vnode.component!.proxy
        } else if (__DEV__) {
          warn(
            `App has already been mounted.\n` +
              `If you want to remount the same app, move your app creation logic ` +
              `into a factory function and create fresh app instances for each ` +
              `mount - e.g. \`const createMyApp = () => createApp(App)\``
          )
        }
      },

      unmount() {
        // ...
      },

      provide(key, value) {
        // ...
      }
    })

    if (__COMPAT__) {
      installAppCompatProperties(app, context, render)
    }

    return app
  }
}

// packages\runtime-core\src\renderer.ts # 2303
const render: RootRenderFunction = (vnode, container, isSVG) => {
    if (vnode == null) {
        if (container._vnode) {
            unmount(container._vnode, null, null, true)
        }
    } else {
        // 首次执行，传入根组件 vnode，参数1是null
        // 首次 执行为渲染
        patch(container._vnode || null, vnode, container, null, null, null, isSVG)
    }
    flushPostFlushCbs()
    container._vnode = vnode
}

// packages\runtime-core\src\renderer.ts # 354
const patch: PatchFn = (
    n1, // 旧节点
    n2, // 新节点
    container,
    anchor = null,
    parentComponent = null,
    parentSuspense = null,
    isSVG = false,
    slotScopeIds = null,
    optimized = __DEV__ && isHmrUpdating ? false : !!n2.dynamicChildren
) => {
    // ...
    switch (type) {
            // 文本
        case Text:
            processText(n1, n2, container, anchor)
            break
            // 注释
        case Comment:
            processCommentNode(n1, n2, container, anchor)
            break
            // 静态
        case Static:
            if (n1 == null) {
                mountStaticNode(n2, container, anchor, isSVG)
            } else if (__DEV__) {
                patchStaticNode(n1, n2, container, isSVG)
            }
            break
            // 分片
        case Fragment:
            processFragment(
                n1,
                n2,
                container,
                anchor,
                parentComponent,
                parentSuspense,
                isSVG,
                slotScopeIds,
                optimized
            )
            break
        default:
            if (shapeFlag & ShapeFlags.ELEMENT) {
            	// element
                processElement(
                    n1,
                    n2,
                    container,
                    anchor,
                    parentComponent,
                    parentSuspense,
                    isSVG,
                    slotScopeIds,
                    optimized
                )
            } else if (shapeFlag & ShapeFlags.COMPONENT) {
                // component
                // 首次渲染
                processComponent(
                    n1,
                    n2,
                    container,
                    anchor,
                    parentComponent,
                    parentSuspense,
                    isSVG,
                    slotScopeIds,
                    optimized
                )
            } else if (shapeFlag & ShapeFlags.TELEPORT) {
                ;(type as typeof TeleportImpl).process(
                    n1 as TeleportVNode,
                    n2 as TeleportVNode,
                    container,
                    anchor,
                    parentComponent,
                    parentSuspense,
                    isSVG,
                    slotScopeIds,
                    optimized,
                    internals
                )
            } else if (__FEATURE_SUSPENSE__ && shapeFlag & ShapeFlags.SUSPENSE) {
                ;(type as typeof SuspenseImpl).process(
                    n1,
                    n2,
                    container,
                    anchor,
                    parentComponent,
                    parentSuspense,
                    isSVG,
                    slotScopeIds,
                    optimized,
                    internals
                )
            } else if (__DEV__) {
                warn('Invalid VNode type:', type, `(${typeof type})`)
            }
    }

    // set ref
    if (ref != null && parentComponent) {
        setRef(ref, n1 && n1.ref, parentSuspense, n2 || n1, !n2)
    }
}

// packages\runtime-core\src\renderer.ts # 1149
const processComponent = (
    n1: VNode | null,
    n2: VNode,
    container: RendererElement,
    anchor: RendererNode | null,
    parentComponent: ComponentInternalInstance | null,
    parentSuspense: SuspenseBoundary | null,
    isSVG: boolean,
    slotScopeIds: string[] | null,
    optimized: boolean
    ) => {
        n2.slotScopeIds = slotScopeIds
        // 首次渲染 n1 为null
        if (n1 == null) {
            if (n2.shapeFlag & ShapeFlags.COMPONENT_KEPT_ALIVE) {
                ;(parentComponent!.ctx as KeepAliveContext).activate(
                    n2,
                    container,
                    anchor,
                    isSVG,
                    optimized
                )
            } else {
                // 首次我们会挂载更组件
                // 子组件时也会挂载
                mountComponent(
                    n2,
                    container,
                    anchor,
                    parentComponent,
                    parentSuspense,
                    isSVG,
                    optimized
                )
            }
        } else {
            updateComponent(n1, n2, optimized)
        }
    }
}


// packages\runtime-core\src\renderer.ts # 1186
const mountComponent: MountComponentFn = (
    initialVNode,
    container,
    anchor,
    parentComponent,
    parentSuspense,
    isSVG,
    optimized
) => {
    // 2.x compat may pre-create the component instance before actually
    // mounting
    const compatMountInstance =
          __COMPAT__ && initialVNode.isCompatRoot && initialVNode.component
    
    // 组件挂载过程：
    // 1.创建组件实例
    const instance: ComponentInternalInstance =
        compatMountInstance ||
        (initialVNode.component = createComponentInstance(
        initialVNode,
        parentComponent,
        parentSuspense
    ))

    // ...

    // 获取 vnode
    // 1.创建一个组件更新函数
    //  1.1.render get vnode
    //  1.2.patch(oldvnode, vnode)
    // 2.创建更新机制 new ReactiveEffect(更新函数)
    setupRenderEffect(
        instance,
        initialVNode,
        container,
        anchor,
        parentSuspense,
        isSVG,
        optimized
    )

    if (__DEV__) {
        popWarningContext()
        endMeasure(instance, `mount`)
    }
}

// packages\runtime-core\src\renderer.ts # 1297
const setupRenderEffect: SetupRenderEffectFn = (
    instance,
    initialVNode,
    container,
    anchor,
    parentSuspense,
    isSVG,
    optimized
) => {
    // 1.创建更新函数
    const componentUpdateFn = () => {
        // ...
    }

    // create reactive effect for rendering
    // 2.创建更新机制（副作用）
    const effect = (instance.effect = new ReactiveEffect(
        // ...
    ))

    // 获取更新机制
    const update = (instance.update = effect.run.bind(effect) as SchedulerJob)
    
    // ...
    
	// 3.首次执行组件更新
    update()
}
```



## 课后问题

### 渲染器是什么？

渲染器是一个对象，它提供了三个方法

- render -- 接收 vdom 转换为 dom，追加到宿主元素
- hydrate -- ssr，服务端讲一个 vnode 生成 html
- createApp -- 创建 app 实例

首次渲染

获取应用实例



### 挂载做了什么事情

- 挂载只执行一次
- 初始化
  - 看到第一次渲染结果
- 建立更新机制
