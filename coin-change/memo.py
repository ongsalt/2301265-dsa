from typing import Callable, Dict, Tuple

def memo(func: Callable) -> Callable:
    cache: Dict[Tuple, object] = {}
    def wrapper(*args, **kwargs):
        key = (args, tuple(sorted(kwargs.items()))) if kwargs else args
        if key in cache:
            # print(f"cache hit for input: {args}")
            return cache[key]
        result = func(*args, **kwargs)
        cache[key] = result
        return result
    return wrapper
