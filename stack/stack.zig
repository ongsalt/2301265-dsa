const std = @import("std");

pub fn Stack(comptime T: type) type {
    return struct {
        allocator: std.mem.Allocator,
        capacity: usize,
        size: usize,
        items: []T,

        const Self = @This();

        fn init(allocator: std.mem.Allocator) !Self {
            const items: []T = try allocator.alloc(T, 128);

            return Self{ .allocator = allocator, .items = items, .capacity = 128, .size = 0 };
        }

        fn free(self: *Self) void {
            self.allocator.free(self.items);
        }

        fn pop(self: *Self) ?T {
            if (self.size == 0) {
                return null;
            }
            const item = self.items[self.size - 1];
            self.items[self.size - 1] = undefined;
            self.size -= 1;
            return item;
        }

        fn push(self: *Self, item: T) !void {
            if (self.size >= self.capacity) {
                self.capacity *= 2;
                self.items = self.allocator.realloc(self.items, self.capacity);
            }
            self.items[self.size] = item;
            self.size += 1;
        }
    };
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}).init;
    const allocator = gpa.allocator();

    var stack = try Stack(u64).init(allocator);
    defer stack.free();
    try stack.push(12);
    try stack.push(24);

    var i = stack.pop();
    std.debug.print("pop: {?}\n", .{i});
    std.debug.print("size: {?}\n", .{stack.size});

    i = stack.pop();
    std.debug.print("pop: {?}\n", .{i});
    std.debug.print("size: {?}\n", .{stack.size});

    i = stack.pop();
    std.debug.print("pop: {?}\n", .{i});
    std.debug.print("size: {?}\n", .{stack.size});
}
