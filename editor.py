# -*- coding=utf8 -*-

import sfml as sf
import os

ressourceDir = '../ressources/'
blockTypes = {
				'Simple':{'file':'Simple.png', 'position':sf.Vector2(0,0),'name':'simple'},
				'Breakable':{'file':'Breakable.png', 'position':sf.Vector2(0,0),'name':'breakable','arg':'3'},
				'Hole':{'file':'Hole.png', 'position':sf.Vector2(0,0),'name':'hole'},
				'Unilateral_down':{'file':'unilateral_down.png', 'position':sf.Vector2(0,0),'name':'unilateral','arg':'down'},
				'Unilateral_up':{'file':'unilateral_up.png', 'position':sf.Vector2(0,0),'name':'unilateral','arg':'up'},
				'Unilateral_right':{'file':'unilateral_right.png', 'position':sf.Vector2(0,0),'name':'unilateral','arg':'right'},
				'Unilateral_left':{'file':'unilateral_left.png', 'position':sf.Vector2(0,0),'name':'unilateral','arg':'left'},
				'C_down':{'file':'Change_down.png', 'position':sf.Vector2(0,0),'name':'change_down'},
				'C_up':{'file':'Change_up.png', 'position':sf.Vector2(0,0),'name':'change_up'},
				'C_right':{'file':'Change_right.png', 'position':sf.Vector2(0,0),'name':'change_right'},
				'C_left':{'file':'Change_left.png', 'position':sf.Vector2(0,0),'name':'change_left'},
				'End':{'file':'Star.png', 'position':sf.Vector2(0,0),'name':'end'},
				'Begin':{'file':'Bille.png', 'position':sf.Vector2(0,0),'name':'begin'},
				'Empty':{'file':'Empty.png', 'position':sf.Vector2(0,0)}
			}

uniqueBlocks = ('Begin','End')

class Editor:
	def __init__(self, fileName):
		self.fileName = fileName
		self.dimX=10
		self.dimY=8
		self.windowDimX = 60*self.dimX
		self.windowDimY = 60*(self.dimY+1+(len(blockTypes)-1)/self.dimX)
		self.gridOffsetY = 60*(1+(len(blockTypes)-1)/self.dimX)
		self.window=sf.RenderWindow(sf.VideoMode(
									self.windowDimX, 
									self.windowDimY), 
									"Editeur")
		self.level = [['Empty' for i in range(self.dimX)] for j in range(self.dimY)]
		self.currentBlock = 'Simple'
		self.loadTextures()
	
	def loadTextures(self):
		for block in blockTypes:
			if len(blockTypes[block]['file']):
				texture = sf.Texture.from_file(ressourceDir+blockTypes[block]['file'])
				blockTypes[block]['texture'] = texture
			else:
				texture = sf.Texture.create(640,480)
				blockTypes[block]['texture'] = texture

	def display(self):
		x,y = 0,0
		blockList = [b for b in blockTypes if b != 'Empty']
		blockList.sort()
		# Display the different blocks to choose from
		for t in blockList:
			s = sf.Sprite(blockTypes[t]['texture'])
			s.position = sf.Vector2(60*x,60*y)
			blockTypes[t]['position'] = s.position
			x += 1
			if x > self.dimX:
				x = 0
				y += 1
			self.window.draw(s)
		# Display the grid
		for y in range(len(self.level)):
			line = self.level[y]
			for x in range(len(line)):
				t = self.level[y][x]
				s = sf.Sprite(blockTypes[t]['texture'])
				s.position = sf.Vector2(60*x,60*y+self.gridOffsetY)
				self.window.draw(s)

	def deleteUniqueBlock(self,b):
		if not b in uniqueBlocks:
			return
		for y in range(len(self.level)):
			line = self.level[y]
			for x in range(len(line)):
				if self.level[y][x] == b:
					self.level[y][x] = 'Empty'

	def handleMouseEvent(self,e):
		if sf.Mouse.is_button_pressed(sf.Mouse.LEFT):
			if e.position.y < self.gridOffsetY:
				for t in blockTypes:
					pos = blockTypes[t]['position']
					if (e.position.x > pos.x and e.position.x < pos.x+60
							and e.position.y > pos.y and e.position.y < pos.y+60):
						self.currentBlock = t
				print(self.currentBlock)
			else:
				x = int(e.position.x/60)
				y = int((e.position.y-self.gridOffsetY)/60)
				if self.currentBlock in uniqueBlocks:
					self.deleteUniqueBlock(self.currentBlock)
				self.level[y][x] = self.currentBlock
		if sf.Mouse.is_button_pressed(sf.Mouse.RIGHT):
			if e.position.y > self.gridOffsetY:
				x = int(e.position.x/60)
				y = int(e.position.y/60 - ((len(blockTypes)-1)/self.dimX+1))
				self.level[y][x] = 'Empty'

	def save(self):
		f = open(self.fileName,mode='w')
		for y in range(len(self.level)):
			line = self.level[y]
			for x in range(len(line)):
				b = self.level[y][x]
				if 'name' in blockTypes[b]:
					s = blockTypes[b]['name']+' '+str(x)+' '+str(y)
					if 'arg' in blockTypes[b]:
						s += ' ' + blockTypes[b]['arg']
					s += '\n'
					f.write(s)
		f.close()

	def run(self):
		while self.window.is_open:
			for event in self.window.events:
				if event==sf.CloseEvent:
					self.window.close()
				if event==sf.MouseButtonEvent:
					self.handleMouseEvent(event)
			self.window.clear(sf.Color.WHITE)
			self.display()
			self.window.display()
		self.save()

fileName = 'level.txt'

ed = Editor(fileName)
ed.run()
