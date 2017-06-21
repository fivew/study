# 信号与槽
```python
# 使用事件名称将信号与曹绑定
QtCore.QMetaObject.connectSlotsByName(Dialog)

@pyqtSlot() #槽函数装饰
def on_pushButtonOK_clicked(self):
	# 将pushButtonOK组件的clicked绑定到该槽函数上
	"""
	Slot documentation goes here.
	"""
	# TODO: not implemented yet
	self.label.setText("hello")

# 手动绑定槽代码如下:
pushButtonOK.clicked.connect(self.test)

```
