
print(_VERSION)
print(package.cpath)

luacdll = require("luacdll")
if luacdll ~= nil then
    r = luacdll.MultTwoNumbers(5.6, 2.17)
    print(r)

    local info = "GetCurrentThreadId() = " .. tostring(luacdll.GetCurrentThreadId()) .. "\n"
    print(info)

    r = luacdll.MultAllNumbers(6, 3, "23423", {2.17}, 1.1)
    info = 'MultAllNumbers(6, 3, "23423", {2.17}, 1.1) = ' .. tostring(r) .. "\n"
    print(info)

    -- New API
    luacdll.ShowMsg(_VERSION)

else
    print("Failed to load the DLL")
end
