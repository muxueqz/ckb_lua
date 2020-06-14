ckb_debug("hello arg")
ckb_debug("hello arg 中文")
ckb_debug(ckb_load_cell_data(3))

local r = ckb_load_tx_hash()
--print(type(r))
--print(r[1])

local n_t = {}
for k, v in pairs(r) do
    n_t[k] = string.format('%x', v)
end

ckb_debug(table.concat(n_t))

local r = ckb_load_script_hash()
--print(type(r))
--print(r[1])

local n_t = {}
for k, v in pairs(r) do
    n_t[k] = string.format('%x', v)
end

ckb_debug(table.concat(n_t))

ckb_debug(ckb_load_script(0))
