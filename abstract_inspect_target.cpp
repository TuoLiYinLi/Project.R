#include "abstract_inspect_target.h"

void abstract_inspect_target::push_nullptr()const
{
	if(pointer_to_this_sizer_button)(*pointer_to_this_sizer_button) = nullptr;
	if (pointer_to_this_inspector)(*pointer_to_this_inspector) = nullptr;
}
