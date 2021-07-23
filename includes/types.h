#ifndef TYPES_H
# define TYPES_H

typedef enum e_key_type
{
	KT_UNRECOGNIZED,
	KT_PRINTABLE,
	KT_CHAR_FUNC,
	KT_UP,
	KT_DOWN,
	KT_RIGHT,
	KT_LEFT,
	KT_DELETE,
	KT_EOL
}	t_key_type;

typedef enum e_motion
{
	MOTION_NULL,
	MOTION_UP,
	MOTION_DOWN,
	MOTION_LEFT,
	MOTION_RIGHT,
	MOTION_PREV,
	MOTION_NEXT
}	t_motion;

#endif