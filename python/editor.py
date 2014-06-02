# -*- coding=utf-8 -*-

import sys
from PyQt4 import QtGui,QtCore

ressourceDir = '../ressources/'
blockTypes = {
				'Simple':{'file':'Simple.png'},
				'Breakable':{'file':'Breakable.png'},
				'Hole':{'file':'Hole.png'},
				'Unilateral_down':{'file':'unilateral_down.png'},
				'Unilateral_up':{'file':'unilateral_up.png'},
				'Unilateral_right':{'file':'unilateral_right.png'},
				'Unilateral_left':{'file':'unilateral_left.png'},
				'C_down':{'file':'Change_down.png'},
				'C_up':{'file':'Change_up.png'},
				'C_right':{'file':'Change_right.png'},
				'C_left':{'file':'Change_left.png'},
				'End':{'file':'Star.png'},
				'Begin':{'file':'Bille.png'},
				'Empty':{'file':'Empty.png'}
			}

uniqueBlocks = ('Begin','End')
spriteSize = 60

class Editor(QtGui.QMainWindow):
	def __init__(self):
		super(Editor, self).__init__()
		# Window Geometry
		self.posX = 0
		self.posY = 0
		self.sizeX = 300
		self.sizeY = 300
		self.dimX = 10
		self.dimY = 8
		# UI initialization
		self.initUI()
		# Level initialization
		self.level = [['Empty' for i in range(self.dimX)] for j in range(self.dimY)]
		self.currentBlock = 'Simple'

	def initUI(self):
		# Central Widget creation
		self.mainWidget = QtGui.QWidget()
		self.mainWidget.resize(self.sizeX,self.sizeY)
		self.setCentralWidget(self.mainWidget)
		# Menu Bar creation
		self.menubar = self.menuBar()
		self.menus = {}
		self.menus['File'] = self.menubar.addMenu('File')
		# Exit App item
		exitAction = QtGui.QAction('Quitter',self)
		exitAction.setShortcut('Ctrl+Q')
		exitAction.triggered.connect(self.close)
		self.menus['File'].addAction(exitAction)

		# Window Layout
		self.grid = QtGui.QGridLayout()
		# TODO : create level view,...
		i,j = 0,0
		blockList = [t for t in blockTypes]
		blockList.sort()
		for t in blockList:
			# Button Creation
			button = QtGui.QPushButton('', self)
			button.clicked.connect(lambda: self.changeCurrentBlock(t))
			button.setIcon(QtGui.QIcon(ressourceDir+blockTypes[t]['file']))
			button.setIconSize(QtCore.QSize(24,24))
			# Button position
			self.grid.addWidget(button,i,j)
			j += 1
			if spriteSize * (j+1) > self.sizeY:
				j = 0
				i += 1
		self.mainWidget.setLayout(self.grid)

		# Geometry initialization
		self.setGeometry(self.posX,self.posY,self.sizeX,self.sizeY)
		self.setWindowTitle("Editeur")


	def changeCurrentBlock(self, block):
		if block in blockTypes:
			self.currentBlock = block

	def save(self,fileName):
		f = open(fileName,mode='w')
		for y,line in enumerate(self.level):
			for x,b in enumerate(line):
				if 'name' in blockTypes[b]:
					s = blockTypes[b]['name']+' '+str(x)+' '+str(y)
					if 'arg' in blockTypes[b]:
						s += ' ' + blockTypes[b]['arg']
					s += '\n'
					f.write(s)
		f.close()

app = QtGui.QApplication(sys.argv)
ed = Editor()
ed.show()
app.exec_()
