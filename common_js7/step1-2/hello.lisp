(defun PrintUserInput()
  (setq name (read-line))
  (format t "Hello ~A~%" name)
)

(PrintUserInput)
