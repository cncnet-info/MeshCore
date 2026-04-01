# Custom Fork Workflow (promicro_e22p)

This repository contains local custom hardware support for ProMicro E22P.
Use this workflow to keep local changes safe while syncing upstream firmware updates.

## Branch model

- Keep `main` aligned with upstream.
- Keep all custom board changes in `feature/promicro-e22p-fw-sync`.

## Initial setup

```bash
git checkout feature/promicro-e22p-fw-sync
```

## Update from upstream

1. Fetch upstream changes:

```bash
git fetch origin
```

2. Rebase custom branch on latest upstream main:

```bash
git checkout feature/promicro-e22p-fw-sync
git rebase origin/main
```

3. Resolve conflicts if needed, then continue rebase:

```bash
git add <resolved-files>
git rebase --continue
```

4. Validate build:

```bash
pio run -e ProMicro_E22P_repeater
```

## Files expected to stay custom

- `variants/promicro_e22p/*`
- `boards/promicro_e22p_nrf52840.json`

## Useful checks before pull/rebase

```bash
git status
git diff -- variants/promicro_e22p boards/promicro_e22p_nrf52840.json
```

## Optional: create patch bundle for backup

```bash
git format-patch origin/main --stdout > promicro_e22p.patch
```

You can re-apply it later with:

```bash
git apply promicro_e22p.patch
```
