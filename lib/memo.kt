/**
 * Returns a memoized version of [fn]. Caches results for each unique input [T].
 */
fun <T, R> memo(fn: (T) -> R): (T) -> R {
    val cache = mutableMapOf<T, R>()
    return { t: T ->
        cache.getOrPut(t) { fn(t) }
    }
}

/**
 * Returns a memoized version of a two-argument function [fn].
 */
fun <A, B, R> memo(fn: (A, B) -> R): (A, B) -> R {
    val cache = mutableMapOf<Pair<A, B>, R>()
    return { a: A, b: B ->
        cache.getOrPut(a to b) { fn(a, b) }
    }
}

/**
 * Returns a memoized version of a vararg function [fn], similar to TS spread args.
 */
fun <R> memo(fn: (vararg Any?) -> R): (vararg Any?) -> R {
    val cache = mutableMapOf<List<Any?>, R>()
    return { vararg args: Any? ->
        val key = args.toList()
        cache.getOrPut(key) { fn(*args) }
    }
}

fun main() {
    // Example: recursive factorial with memoization
    val factorial: (Int) -> Int = memo { n ->
        if (n == 0 || n == 1) {
            1
        } else {
            println("fallthrough")
            n * factorial(n - 1)
        }
    }

    println(factorial(8))
    println(factorial(9))
    println(factorial(9))
    println(factorial(9))
    println(factorial(9))
}
