#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist
from std_msgs.msg import Bool , Int16
import time
from math import pi

wheel_dia = 0.1
wheel_sep = 0.31
rpm = 200

cir = pi * wheel_dia

top_speed = ( cir * rpm ) / 60
top_ang = ( top_speed * 2 ) / wheel_sep

def callback(data):

	global wheel_dia
	global wheel_sep
	global rpm
	global top_speed

	ldir_pub = rospy.Publisher('/ldir', Bool, queue_size = 10)
	rdir_pub = rospy.Publisher('/rdir', Bool, queue_size = 10)

	lpwm_pub = rospy.Publisher('/lpwm', Int16, queue_size = 10)
	rpwm_pub = rospy.Publisher('/rpwm', Int16, queue_size = 10)

	print(data)
	

	lin = data.linear.x
	ang = data.angular.z

	

	VrplusVl = 2 * lin
	VrminusVl = wheel_sep * ang

	Vr = (VrplusVl+VrminusVl)/2
	Vl = VrplusVl - Vr

	

	Vr_abs = abs(Vr)
	Vl_abs = abs(Vl)

	lpwm = int ( ( Vl_abs / top_speed ) * 255 )
	rpwm = int ( ( Vr_abs / top_speed ) * 255 )

	
	lpwm_pub.publish(lpwm)
	rpwm_pub.publish(rpwm)
	if Vl > 0:
		ldir_pub.publish(1)
	else:
		ldir_pub.publish(0)

	if Vr > 0:
		rdir_pub.publish(1)
	else:
		rdir_pub.publish(0)

	print('lp:'+str(lpwm)+'rp: '+str(rpwm))
	print('Vl: '+str(Vl)+"\t"+'Vr: '+str(Vr))

def differential():

	rospy.init_node('differential', anonymous = False)
	rospy.Subscriber('/cmd_vel', Twist, callback)
	rospy.spin()


if __name__== '__main__' :

	print ('Motor RPM: '+str(rpm))
	print ('Wheel Diameter: '+str(wheel_dia))
	print ('Wheel Separation: '+str(wheel_sep))
	print ('Top Speed: '+str(top_speed))
	print ('Top Angular: '+str(top_ang))
	differential()
