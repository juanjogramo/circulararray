.PHONY: clean All

All:
	@echo "----------Building project:[ circulararray - Debug ]----------"
	@"$(MAKE)" -f  "circulararray.mk"
clean:
	@echo "----------Cleaning project:[ circulararray - Debug ]----------"
	@"$(MAKE)" -f  "circulararray.mk" clean
