
(cl:in-package :asdf)

(defsystem "ros_basics-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "iotSensor" :depends-on ("_package_iotSensor"))
    (:file "_package_iotSensor" :depends-on ("_package"))
  ))