from xml.etree.ElementTree import ElementTree

tree = ElementTree()
info = tree.parse('info.xml')

print 'Title: '
print info.find('title').text
print '\n'

print 'Client: '
print info.find('client').text
print '\n'

print 'Year: '
print info.find('year').text
print '\n'

print 'Type: '
print info.find('type').text
print '\n'

print 'About: '
print info.find('about').text
print '\n'
