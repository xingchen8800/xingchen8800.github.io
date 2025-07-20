from manim import *

class ScapegoatTreeAnimation(Scene):
    def construct(self):
        # 创建不平衡的替罪羊树
        nodes = self.create_unbalanced_tree()
        
        # 展示初始树结构
        self.play(Create(nodes["tree"]))
        self.wait(1)
        
        # 标记要删除的节点（节点3）
        deleted_node = nodes["nodes"][3]
        deleted_node_label = nodes["labels"][3]
        deleted_node_id = nodes["ids"][3]
        cross = Cross(deleted_node).scale(0.8)
        self.play(Create(cross))
        self.wait(1)
        
        # 展示中序遍历过程
        self.in_order_traversal_animation(nodes)
        
        # 展示节点回收
        self.show_node_recycling(deleted_node, deleted_node_id, deleted_node_label, cross)
        
        self.wait(2)
    
    def create_unbalanced_tree(self):
        # 创建不平衡的树结构
        root = Circle(radius=0.4, color=BLUE, fill_opacity=1).shift(UP*2)
        root_label = Text("5").scale(0.5).move_to(root)
        root_id = Text("0", color=YELLOW).scale(0.4).next_to(root, UP, buff=0.1)
        
        node1 = Circle(radius=0.4, color=BLUE, fill_opacity=1).shift(UP*0.5 + LEFT*2)
        node1_label = Text("3").scale(0.5).move_to(node1)
        node1_id = Text("1", color=YELLOW).scale(0.4).next_to(node1, UP, buff=0.1)
        
        node2 = Circle(radius=0.4, color=BLUE, fill_opacity=1).shift(UP*0.5 + RIGHT*1)
        node2_label = Text("7").scale(0.5).move_to(node2)
        node2_id = Text("2", color=YELLOW).scale(0.4).next_to(node2, UP, buff=0.1)
        
        node3 = Circle(radius=0.4, color=BLUE, fill_opacity=1).shift(DOWN*1 + LEFT*3)
        node3_label = Text("1").scale(0.5).move_to(node3)
        node3_id = Text("3", color=YELLOW).scale(0.4).next_to(node3, UP, buff=0.1)
        
        node4 = Circle(radius=0.4, color=BLUE, fill_opacity=1).shift(DOWN*1 + LEFT*1)
        node4_label = Text("4").scale(0.5).move_to(node4)
        node4_id = Text("4", color=YELLOW).scale(0.4).next_to(node4, UP, buff=0.1)
        
        node5 = Circle(radius=0.4, color=BLUE, fill_opacity=1).shift(DOWN*1 + RIGHT*2)
        node5_label = Text("8").scale(0.5).move_to(node5)
        node5_id = Text("5", color=YELLOW).scale(0.4).next_to(node5, UP, buff=0.1)
        
        # 边
        edge1 = Line(root.get_bottom(), node1.get_top(), buff=0.1)
        edge2 = Line(root.get_bottom(), node2.get_top(), buff=0.1)
        edge3 = Line(node1.get_bottom(), node3.get_top(), buff=0.1)
        edge4 = Line(node1.get_bottom(), node4.get_top(), buff=0.1)
        edge5 = Line(node2.get_bottom(), node5.get_top(), buff=0.1)
        
        # 组合所有元素
        tree = VGroup(
            root, root_label, root_id,
            node1, node1_label, node1_id,
            node2, node2_label, node2_id,
            node3, node3_label, node3_id,
            node4, node4_label, node4_id,
            node5, node5_label, node5_id,
            edge1, edge2, edge3, edge4, edge5
        )
        
        return {
            "tree": tree,
            "nodes": [root, node1, node2, node3, node4, node5],
            "ids": [root_id, node1_id, node2_id, node3_id, node4_id, node5_id],
            "labels": [root_label, node1_label, node2_label, node3_label, node4_label, node5_label],
            "edges": [edge1, edge2, edge3, edge4, edge5]
        }
    
    def in_order_traversal_animation(self, nodes_dict):
        # 模拟递归的中序遍历步骤
        traversal_steps = [
            (0, "enter"),  # 进入根节点
            (0, "record"), # 记录根节点(但实际中序应该在访问右子树前记录)
            (1, "enter"),  # 进入节点1
            (1, "record"), # 记录节点1
            (3, "enter"),  # 进入节点3
            (3, "record"), # 记录节点3(被删除)
            (4, "enter"),  # 进入节点4
            (4, "record"), # 记录节点4
            (2, "enter"),  # 进入节点2
            (2, "record"), # 记录节点2
            (5, "enter"),  # 进入节点5
            (5, "record")  # 记录节点5
        ]
        
        # 创建order数组和treeStack
        order_text = Text("order[]: ").scale(0.6).to_edge(DOWN).shift(UP*1 + LEFT*3)
        order_array = VGroup(*[Square(side_length=0.6, color=WHITE, fill_opacity=0.2) 
                             for _ in range(5)]).arrange(RIGHT, buff=0.1).next_to(order_text, RIGHT)
        
        stack_text = Text("treeStack: ").scale(0.6).to_edge(DOWN).shift(DOWN*0 + LEFT*3)
        stack_array = VGroup(*[Square(side_length=0.6, color=WHITE, fill_opacity=0.2) 
                             for _ in range(1)]).arrange(RIGHT, buff=0.1).next_to(stack_text, RIGHT)
        
        self.play(Write(order_text), Create(order_array))
        self.play(Write(stack_text), Create(stack_array))
        self.wait(0.5)
        
        order_index = 0
        
        for node_idx, action in traversal_steps:
            node = nodes_dict["nodes"][node_idx]
            node_id = nodes_dict["ids"][node_idx]
            node_label = nodes_dict["labels"][node_idx]
            
            if action == "enter":
                # 遍历步骤：用圆圈标记
                circle = Circle(radius=0.5, color=YELLOW, stroke_width=3).move_to(node)
                self.play(Create(circle), run_time=0.5)
                self.wait(0.3)
                self.play(FadeOut(circle), run_time=0.3)
                
            elif action == "record":
                # 记录步骤：用高亮表示
                highlight = node.copy().set_fill(ORANGE, opacity=0.3)
                id_highlight = node_id.copy().set_color(RED)
                self.play(
                    node.animate.set_fill(ORANGE, opacity=0.3),
                    node_id.animate.set_color(RED),
                    run_time=0.5
                )
                self.wait(0.3)
                
                if node_idx == 3:  # 被删除的节点
                    # 移动到treeStack
                    moving_id = node_id.copy()
                    self.add(moving_id)
                    
                    self.play(
                        moving_id.animate.scale(1.2).move_to(stack_array[0]).set_color(RED),
                        run_time=0.7
                    )
                    
                    stack_box = stack_array[0].copy().set_fill(RED, opacity=0.3)
                    self.play(FadeIn(stack_box))
                    
                    self.remove(moving_id)
                    stack_label = Text("3").scale(0.5).move_to(stack_array[0])
                    self.play(Write(stack_label))
                else:
                    # 移动到order数组
                    moving_id = node_id.copy()
                    self.add(moving_id)
                    
                    self.play(
                        moving_id.animate.scale(1.2).move_to(order_array[order_index]).set_color(GREEN),
                        run_time=0.7
                    )
                    
                    order_box = order_array[order_index].copy().set_fill(GREEN, opacity=0.3)
                    self.play(FadeIn(order_box))
                    
                    self.remove(moving_id)
                    order_label = Text(str(node_idx)).scale(0.5).move_to(order_array[order_index])
                    self.play(Write(order_label))
                    
                    order_index += 1
                
                # 恢复节点颜色
                self.play(
                    node.animate.set_fill(BLUE, opacity=1),
                    node_id.animate.set_color(YELLOW),
                    run_time=0.3
                )
                self.wait(0.3)
    
    def show_node_recycling(self, deleted_node, deleted_node_id, deleted_node_label, cross):
        # 展示节点被回收
        recycle_box = Rectangle(width=1.5, height=1, color=RED).to_edge(UR)
        recycle_text = Text("回收节点").scale(0.5).next_to(recycle_box, DOWN)
        
        # 确保节点值"1"也被移动
        self.play(
            deleted_node.animate.move_to(recycle_box.get_center()),
            deleted_node_id.animate.move_to(recycle_box.get_center()),
            deleted_node_label.animate.move_to(recycle_box.get_center()),
            cross.animate.move_to(recycle_box.get_center()),
            Create(recycle_box),
            Write(recycle_text)
        )
        self.wait(1)
        
        # 节点消失表示被回收
        self.play(
            FadeOut(deleted_node),
            FadeOut(deleted_node_id),
            FadeOut(deleted_node_label),
            FadeOut(cross),
            FadeOut(recycle_box),
            FadeOut(recycle_text)
        )